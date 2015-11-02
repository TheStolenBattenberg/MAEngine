/**
*
* NOTE :-> See note inside ObjectModel.h.
* 
*/
#include "dllbackend.h"

namespace {
	MADLLBackend MARenderBackend;
}

int MD2Model::MD2Load(char* mdl_name, LPCWSTR tex_name)
{
	try {
		std::ifstream f_MD2;
		f_MD2.open(mdl_name, std::ios::in | std::ios::binary); 
		
		if (!f_MD2.is_open())
		{ 
			throw Exception("Failed to open MD2 file."); 
		}
		try {
			is_valid = false;
				FetchHeader(f_MD2);
				ValidateHeader();

				FetchFrameData(f_MD2);
				FetchIndexData(f_MD2);
				FetchTextureData(f_MD2);
			is_valid = true;
		}
		catch (Exception& e)
		{
			MessageBoxA(NULL, e.exception, "MD2 Error!", MB_ICONERROR);
		}
	}
	catch (Exception& e)
	{
		MessageBoxA(NULL, e.exception, "MD2 Error!", MB_ICONERROR);
	}

	D3DXCreateTextureFromFile(MARenderBackend.d3ddev, tex_name, &Texture);
	if (!Texture)
	{
		MessageBoxA(NULL, "Couldn't Load Texture!", "MD2 Error!", MB_ICONERROR);
	}
	return 1;
}

void MD2Model::FetchHeader(std::ifstream& f_MD2)
{
	f_MD2.seekg(0, std::ios::beg);
	f_MD2.read((char*)& Header, sizeof(MD2Type::Header));
}

void MD2Model::FetchFrameData(std::ifstream& f_MD2)
{
	int MD2_FrameSize = (Header.framesize * Header.num_frames);
	char* FrameBuffer = new char[MD2_FrameSize];

	f_MD2.seekg(Header.ofs_frames, std::ios::beg);
	f_MD2.read((char*)FrameBuffer, MD2_FrameSize);

	MD2_POSITION_VERTEX* Vertices = new MD2_POSITION_VERTEX[Header.num_xyz];

	MD2Type::Frame* CurrentFrame = (MD2Type::Frame*)FrameBuffer;
	for (int f = 0; f < Header.num_frames; f++)
	{
		CurrentFrame = (MD2Type::Frame*) &FrameBuffer[Header.framesize * f];
		
		for (int v = 0; v < Header.num_xyz; v++)
		{
			for (int i = 0; i < 3; i++)
			{
				Vertices[v].a[i] = (CurrentFrame->verticies[v].vertex[i] * CurrentFrame->scale[i]) + CurrentFrame->translate[i];
			}
		}


		HRESULT result = MARenderBackend.d3ddev->CreateVertexBuffer(sizeof(MD2_POSITION_VERTEX) * Header.num_xyz, D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &MD2VB[f], 0);
		if (FAILED(result))
		{
			MessageBoxA(0, "Couldn't create the DirectX9 Vertex Buffers!", "Fatal Error!", MB_ICONERROR);
			return;
		}

		void* MemoryPointer = 0;
		MD2VB[f]->Lock(0, 0, &MemoryPointer, 0);
		memcpy(MemoryPointer, Vertices, sizeof(MD2_POSITION_VERTEX)*Header.num_xyz);
		MD2VB[f]->Unlock();

		Frames++;
	}

	delete[] Vertices;
	delete[] FrameBuffer;
}

void MD2Model::FetchIndexData(std::ifstream& f_MD2)
{
	MD2Type::Triangle * TriangleBuffer = new MD2Type::Triangle[Header.num_tris];
	MD2Type::index_buffer* IndexBuffer = new MD2Type::index_buffer[Header.num_tris];

	f_MD2.seekg(Header.ofs_tris, std::ios::beg);
	f_MD2.read((char*)TriangleBuffer, sizeof(MD2Type::Triangle) * Header.num_tris);

	for (int i = 0; i < Header.num_tris; i++)
	{
		IndexBuffer[i][0] = TriangleBuffer[i].vertex_indicies[0];
		IndexBuffer[i][1] = TriangleBuffer[i].vertex_indicies[1];
		IndexBuffer[i][2] = TriangleBuffer[i].vertex_indicies[2];
	}

	MARenderBackend.d3ddev->CreateIndexBuffer(sizeof(MD2Type::index_buffer) * Header.num_tris, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &MD2IB, 0);

	void* MemoryPointer;
	MD2IB->Lock(0, 0, &MemoryPointer, 0);
	memcpy(MemoryPointer, IndexBuffer, sizeof(MD2Type::index_buffer) * Header.num_tris);
	MD2IB->Unlock();

	delete[] IndexBuffer;
	delete[] TriangleBuffer;
}

void MD2Model::FetchTextureData(std::ifstream& f_MD2)
{
	MD2Type::Texcoord* CoordBuffer = new MD2Type::Texcoord[Header.num_st];
	MD2_TEXTURE_VERTEX* TextureBuffer = new MD2_TEXTURE_VERTEX[Header.num_st];

	f_MD2.seekg(Header.ofs_st, std::ios::beg);
	f_MD2.read((char*)CoordBuffer, sizeof(MD2Type::Texcoord) * Header.num_st);

	for (int i = 0; i < Header.num_st; i++)
	{
		TextureBuffer[i].s = ((float)CoordBuffer[i].s / (float)Header.skinwidth);
		TextureBuffer[i].t = ((float)CoordBuffer[i].t / (float)Header.skinheight);
	}

	MD2_TEXTURE_VERTEX* VertexTextureBuffer = new MD2_TEXTURE_VERTEX[Header.num_xyz];
	MD2Type::Triangle* TriangleBuffer = new MD2Type::Triangle[Header.num_tris];

	f_MD2.seekg(Header.ofs_tris, std::ios::beg);
	f_MD2.read((char*)TriangleBuffer, sizeof(MD2Type::Triangle) * Header.num_tris);

	for (int t = 0; t < Header.num_tris; t++)
	{
		for (int i = 0; i < 3; i++)
		{
			int Vertex = TriangleBuffer[t].vertex_indicies[i];
			VertexTextureBuffer[Vertex].s = TextureBuffer[TriangleBuffer[t].texture_indicies[i]].s;
			VertexTextureBuffer[Vertex].t = TextureBuffer[TriangleBuffer[t].texture_indicies[i]].t;
		}
	}

	MARenderBackend.d3ddev->CreateVertexBuffer(sizeof(MD2_TEXTURE_VERTEX) * Header.num_xyz, 0, 0, D3DPOOL_MANAGED, &MD2TB, 0);

	void* MemoryPointer;
	MD2TB->Lock(0, 0, &MemoryPointer, 0);
	memcpy(MemoryPointer, VertexTextureBuffer, sizeof(MD2_TEXTURE_VERTEX) * Header.num_xyz);
	MD2TB->Unlock();

	delete[] TriangleBuffer;
	delete[] VertexTextureBuffer;
	delete[] TextureBuffer;
	delete[] CoordBuffer;
}

void MD2Model::ValidateHeader()
{
	if (Header.magic_number != 844121161 || Header.version != 8 || Header.framesize == 0)
	{
		throw Exception("The MD2 header is corrupt.");
	}
}

IDirect3DVertexBuffer9* MD2Model::FetchVB(int frame)
{
	return MD2VB[frame];
}

IDirect3DVertexBuffer9* MD2Model::FetchTB(void)
{
	return MD2TB;
}

IDirect3DIndexBuffer9* MD2Model::FetchIB(void)
{
	return MD2IB;
}

IDirect3DTexture9* MD2Model::FetchTexture(void)
{
	return Texture;
}

int MD2Model::FetchVertexCount(void)
{
	return Header.num_xyz;
}

int MD2Model::FetchTriangleCount(void)
{
	return Header.num_tris;
}

int MD2Model::FetchFrameCount(void)
{
	return Header.num_frames;
}

char* MD2Model::FetchFrameName(int frame)
{
	return 0;
}

MD2Model::MD2Model(void)
{
	is_valid = false;
	Frames = 0;

	memset(&Header, 0, sizeof(MD2Type::Header));

	for (int i = 0; i < 512; i++)
	{
		MD2VB[i] = NULL;
	}
	MD2TB = NULL;
	MD2IB = NULL;
}

MD2Model::~MD2Model(void)
{
	for (int i = 0; i < Frames; i++)
	{
		MD2VB[i]->Release();
	}
	MD2TB->Release();
	MD2IB->Release();
}
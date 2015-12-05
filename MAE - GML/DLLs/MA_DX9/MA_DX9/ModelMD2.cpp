#include "Main.h"
#include "Utils.h"
#include "Mesh.h"
#include "ModelMD2.h"

namespace MD2Type
{
	enum
	{
		Version     = 0x00000008ul,
		MagicNumber = 0x32504449ul
	};

	struct Header
	{
		uint magicNumber;
		uint version;

		uint skinWidth;
		uint skinHeight;
		uint frameSize;

		uint numSkin;
		uint numVert;
		uint numST;
		uint numTris;
		uint numGLCmds;
		uint numFrames;

		uint ofsSkins;
		uint ofsST;
		uint ofsTris;
		uint ofsFrames;
		uint ofsGLCmds;
		uint ofsEnd;
	};

	struct Vertex
	{
		ubyte vertex[3];
		ubyte normInd;
	};

	struct Frame
	{
		float  scale[3];
		float  translate[3];
		char   name[16];
		Vertex verticies[1];
	};

	struct Triangle
	{
		short vertInd[3];
		short texInd[3];
	};

	typedef short IndexBuffer[3];

	struct Texcoord
	{
		short s, t;
	};
};

Normal MD2Normals[] =
{
	{-0.525731f,  0.000000f,  0.850651f},
	{-0.442863f,  0.238856f,  0.864188f},
	{-0.295242f,  0.000000f,  0.955423f},
	{-0.309017f,  0.500000f,  0.809017f},
	{-0.162460f,  0.262866f,  0.951056f},
	{ 0.000000f,  0.000000f,  1.000000f},
	{ 0.000000f,  0.850651f,  0.525731f},
	{-0.147621f,  0.716567f,  0.681718f},
	{ 0.147621f,  0.716567f,  0.681718f},
	{ 0.000000f,  0.525731f,  0.850651f},
	{ 0.309017f,  0.500000f,  0.809017f},
	{ 0.525731f,  0.000000f,  0.850651f},
	{ 0.295242f,  0.000000f,  0.955423f},
	{ 0.442863f,  0.238856f,  0.864188f},
	{ 0.162460f,  0.262866f,  0.951056f},
	{-0.681718f,  0.147621f,  0.716567f},
	{-0.809017f,  0.309017f,  0.500000f},
	{-0.587785f,  0.425325f,  0.688191f},
	{-0.850651f,  0.525731f,  0.000000f},
	{-0.864188f,  0.442863f,  0.238856f},
	{-0.716567f,  0.681718f,  0.147621f},
	{-0.688191f,  0.587785f,  0.425325f},
	{-0.500000f,  0.809017f,  0.309017f},
	{-0.238856f,  0.864188f,  0.442863f},
	{-0.425325f,  0.688191f,  0.587785f},
	{-0.716567f,  0.681718f, -0.147621f},
	{-0.500000f,  0.809017f, -0.309017f},
	{-0.525731f,  0.850651f,  0.000000f},
	{ 0.000000f,  0.850651f, -0.525731f},
	{-0.238856f,  0.864188f, -0.442863f},
	{ 0.000000f,  0.955423f, -0.295242f},
	{-0.262866f,  0.951056f, -0.162460f},
	{ 0.000000f,  1.000000f,  0.000000f},
	{ 0.000000f,  0.955423f,  0.295242f},
	{-0.262866f,  0.951056f,  0.162460f},
	{ 0.238856f,  0.864188f,  0.442863f},
	{ 0.262866f,  0.951056f,  0.162460f},
	{ 0.500000f,  0.809017f,  0.309017f},
	{ 0.238856f,  0.864188f, -0.442863f},
	{ 0.262866f,  0.951056f, -0.162460f},
	{ 0.500000f,  0.809017f, -0.309017f},
	{ 0.850651f,  0.525731f,  0.000000f},
	{ 0.716567f,  0.681718f,  0.147621f},
	{ 0.716567f,  0.681718f, -0.147621f},
	{ 0.525731f,  0.850651f,  0.000000f},
	{ 0.425325f,  0.688191f,  0.587785f},
	{ 0.864188f,  0.442863f,  0.238856f},
	{ 0.688191f,  0.587785f,  0.425325f},
	{ 0.809017f,  0.309017f,  0.500000f},
	{ 0.681718f,  0.147621f,  0.716567f},
	{ 0.587785f,  0.425325f,  0.688191f},
	{ 0.955423f,  0.295242f,  0.000000f},
	{ 1.000000f,  0.000000f,  0.000000f},
	{ 0.951056f,  0.162460f,  0.262866f},
	{ 0.850651f, -0.525731f,  0.000000f},
	{ 0.955423f, -0.295242f,  0.000000f},
	{ 0.864188f, -0.442863f,  0.238856f},
	{ 0.951056f, -0.162460f,  0.262866f},
	{ 0.809017f, -0.309017f,  0.500000f},
	{ 0.681718f, -0.147621f,  0.716567f},
	{ 0.850651f,  0.000000f,  0.525731f},
	{ 0.864188f,  0.442863f, -0.238856f},
	{ 0.809017f,  0.309017f, -0.500000f},
	{ 0.951056f,  0.162460f, -0.262866f},
	{ 0.525731f,  0.000000f, -0.850651f},
	{ 0.681718f,  0.147621f, -0.716567f},
	{ 0.681718f, -0.147621f, -0.716567f},
	{ 0.850651f,  0.000000f, -0.525731f},
	{ 0.809017f, -0.309017f, -0.500000f},
	{ 0.864188f, -0.442863f, -0.238856f},
	{ 0.951056f, -0.162460f, -0.262866f},
	{ 0.147621f,  0.716567f, -0.681718f},
	{ 0.309017f,  0.500000f, -0.809017f},
	{ 0.425325f,  0.688191f, -0.587785f},
	{ 0.442863f,  0.238856f, -0.864188f},
	{ 0.587785f,  0.425325f, -0.688191f},
	{ 0.688191f,  0.587785f, -0.425325f},
	{-0.147621f,  0.716567f, -0.681718f},
	{-0.309017f,  0.500000f, -0.809017f},
	{ 0.000000f,  0.525731f, -0.850651f},
	{-0.525731f,  0.000000f, -0.850651f},
	{-0.442863f,  0.238856f, -0.864188f},
	{-0.295242f,  0.000000f, -0.955423f},
	{-0.162460f,  0.262866f, -0.951056f},
	{ 0.000000f,  0.000000f, -1.000000f},
	{ 0.295242f,  0.000000f, -0.955423f},
	{ 0.162460f,  0.262866f, -0.951056f},
	{-0.442863f, -0.238856f, -0.864188f},
	{-0.309017f, -0.500000f, -0.809017f},
	{-0.162460f, -0.262866f, -0.951056f},
	{ 0.000000f, -0.850651f, -0.525731f},
	{-0.147621f, -0.716567f, -0.681718f},
	{ 0.147621f, -0.716567f, -0.681718f},
	{ 0.000000f, -0.525731f, -0.850651f},
	{ 0.309017f, -0.500000f, -0.809017f},
	{ 0.442863f, -0.238856f, -0.864188f},
	{ 0.162460f, -0.262866f, -0.951056f},
	{ 0.238856f, -0.864188f, -0.442863f},
	{ 0.500000f, -0.809017f, -0.309017f},
	{ 0.425325f, -0.688191f, -0.587785f},
	{ 0.716567f, -0.681718f, -0.147621f},
	{ 0.688191f, -0.587785f, -0.425325f},
	{ 0.587785f, -0.425325f, -0.688191f},
	{ 0.000000f, -0.955423f, -0.295242f},
	{ 0.000000f, -1.000000f,  0.000000f},
	{ 0.262866f, -0.951056f, -0.162460f},
	{ 0.000000f, -0.850651f,  0.525731f},
	{ 0.000000f, -0.955423f,  0.295242f},
	{ 0.238856f, -0.864188f,  0.442863f},
	{ 0.262866f, -0.951056f,  0.162460f},
	{ 0.500000f, -0.809017f,  0.309017f},
	{ 0.716567f, -0.681718f,  0.147621f},
	{ 0.525731f, -0.850651f,  0.000000f},
	{-0.238856f, -0.864188f, -0.442863f},
	{-0.500000f, -0.809017f, -0.309017f},
	{-0.262866f, -0.951056f, -0.162460f},
	{-0.850651f, -0.525731f,  0.000000f},
	{-0.716567f, -0.681718f, -0.147621f},
	{-0.716567f, -0.681718f,  0.147621f},
	{-0.525731f, -0.850651f,  0.000000f},
	{-0.500000f, -0.809017f,  0.309017f},
	{-0.238856f, -0.864188f,  0.442863f},
	{-0.262866f, -0.951056f,  0.162460f},
	{-0.864188f, -0.442863f,  0.238856f},
	{-0.809017f, -0.309017f,  0.500000f},
	{-0.688191f, -0.587785f,  0.425325f},
	{-0.681718f, -0.147621f,  0.716567f},
	{-0.442863f, -0.238856f,  0.864188f},
	{-0.587785f, -0.425325f,  0.688191f},
	{-0.309017f, -0.500000f,  0.809017f},
	{-0.147621f, -0.716567f,  0.681718f},
	{-0.425325f, -0.688191f,  0.587785f},
	{-0.162460f, -0.262866f,  0.951056f},
	{ 0.442863f, -0.238856f,  0.864188f},
	{ 0.162460f, -0.262866f,  0.951056f},
	{ 0.309017f, -0.500000f,  0.809017f},
	{ 0.147621f, -0.716567f,  0.681718f},
	{ 0.000000f, -0.525731f,  0.850651f},
	{ 0.425325f, -0.688191f,  0.587785f},
	{ 0.587785f, -0.425325f,  0.688191f},
	{ 0.688191f, -0.587785f,  0.425325f},
	{-0.955423f,  0.295242f,  0.000000f},
	{-0.951056f,  0.162460f,  0.262866f},
	{-1.000000f,  0.000000f,  0.000000f},
	{-0.850651f,  0.000000f,  0.525731f},
	{-0.955423f, -0.295242f,  0.000000f},
	{-0.951056f, -0.162460f,  0.262866f},
	{-0.864188f,  0.442863f, -0.238856f},
	{-0.951056f,  0.162460f, -0.262866f},
	{-0.809017f,  0.309017f, -0.500000f},
	{-0.864188f, -0.442863f, -0.238856f},
	{-0.951056f, -0.162460f, -0.262866f},
	{-0.809017f, -0.309017f, -0.500000f},
	{-0.681718f,  0.147621f, -0.716567f},
	{-0.681718f, -0.147621f, -0.716567f},
	{-0.850651f,  0.000000f, -0.525731f},
	{-0.688191f,  0.587785f, -0.425325f},
	{-0.587785f,  0.425325f, -0.688191f},
	{-0.425325f,  0.688191f, -0.587785f},
	{-0.425325f, -0.688191f, -0.587785f},
	{-0.587785f, -0.425325f, -0.688191f},
	{-0.688191f, -0.587785f, -0.425325f}
};

MD2Model::~MD2Model()
{
	for (uint i = 0; i < vertBufs.size(); ++i)
		if (vertBufs[i] != 0)
			vertBufs[i]->Release();

	if (texBuf != 0)
		texBuf->Release();

	if (indBuf != 0)
		indBuf->Release();

	if (tex != 0)
		tex->Release();

	if (decl != 0)
		decl->Release();
}

bool MD2Model::load(std::string model, bool normals)
{
	this->normals = normals;

	std::ifstream f(model, std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		mamain->err.onError("Failed to open MD2 file.");
		return 0;
	}

	/**
	* Load and validate MD2 Header
	*/

	MD2Type::Header h;

	f.read((char*)&h, sizeof(h));

	if (h.magicNumber != MD2Type::MagicNumber || h.version != MD2Type::Version || h.frameSize == 0)
	{
		mamain->err.onError("The MD2 header is corrupt.");
		return 0;
	}

	triCount  = h.numTris;
	vertCount = h.numVert;

	/**
	* Load frame data
	*/

	vertBufs.reserve(h.numFrames);

	ubyte* FrameBuffer = new ubyte[h.frameSize * h.numFrames];

	f.seekg(h.ofsFrames, std::ios::beg);
	f.read((char*)FrameBuffer, h.frameSize * h.numFrames);

	MD2Type::Frame* CurrentFrame;

	for (uint frame = 0; frame < h.numFrames; ++frame)
	{
		CurrentFrame = (MD2Type::Frame*) &FrameBuffer[h.frameSize * frame];

		LPDIRECT3DVERTEXBUFFER9 vb;

		HRESULT result = mamain->d3ddev->CreateVertexBuffer(h.numVert * (normals ? sizeof(VertNorm) : sizeof(Vertex)), 0, 0, D3DPOOL_DEFAULT, &vb, 0);

		if (FAILED(result))
		{
			mamain->err.onErrorDX9("Couldn't create the DirectX9 Vertex Buffer!", result);

			delete[] FrameBuffer;

			return 0;
		}

		if (normals)
		{
			VertNorm* Vertices;
			vb->Lock(0, 0, (void**) &Vertices, 0);

			for (uint vert = 0; vert < h.numVert; ++vert) {
				for (uint i = 0; i < 3; i++)
					Vertices[vert].v.raw[i] = (CurrentFrame->verticies[vert].vertex[i] * CurrentFrame->scale[i]) + CurrentFrame->translate[i];

				Vertices[vert].n = MD2Normals[CurrentFrame->verticies[vert].normInd];
			}

			vb->Unlock();
		}
		else
		{
			Vertex* Vertices;
			vb->Lock(0, 0, (void**) &Vertices, 0);

			for (uint vert = 0; vert < h.numVert; ++vert)
				for (uint i = 0; i < 3; i++)
					Vertices[vert].raw[i] = (CurrentFrame->verticies[vert].vertex[i] * CurrentFrame->scale[i]) + CurrentFrame->translate[i];

			vb->Unlock();
		}

		vertBufs.push_back(vb);
	}

	delete[] FrameBuffer;

	/**
	* Load triangle data
	*/

	MD2Type::Triangle* TriangleBuffer = new MD2Type::Triangle[h.numTris];

	f.seekg(h.ofsTris, std::ios::beg);
	f.read((char*)TriangleBuffer, h.numTris * sizeof(*TriangleBuffer));

	/**
	* Load index data
	*/

	HRESULT result = mamain->d3ddev->CreateIndexBuffer(h.numTris * sizeof(MD2Type::IndexBuffer), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indBuf, 0);

	if (FAILED(result))
	{
		mamain->err.onErrorDX9("Couldn't create the DirectX9 Index Buffer!", result);

		delete[] TriangleBuffer;

		return 0;
	}

	MD2Type::IndexBuffer* IndexBuffer;
	indBuf->Lock(0, 0, (void**)&IndexBuffer, 0);

	for (uint i = 0; i < h.numTris; ++i)
	{
		IndexBuffer[i][0] = TriangleBuffer[i].vertInd[0];
		IndexBuffer[i][1] = TriangleBuffer[i].vertInd[1];
		IndexBuffer[i][2] = TriangleBuffer[i].vertInd[2];
	}

	indBuf->Unlock();

	/**
	* Load texture coordinates
	*/

	MD2Type::Texcoord* CoordBuffer = new MD2Type::Texcoord[h.numST];

	f.seekg(h.ofsST, std::ios::beg);
	f.read((char*)CoordBuffer, h.numST * sizeof(*CoordBuffer));

	result = mamain->d3ddev->CreateVertexBuffer(h.numVert * sizeof(TexCoord), 0, 0, D3DPOOL_DEFAULT, &texBuf, 0);

	if (FAILED(result))
	{
		mamain->err.onErrorDX9("Couldn't create the DirectX9 Vertex Buffer!", result);

		delete[] CoordBuffer;
		delete[] TriangleBuffer;

		return 0;
	}

	TexCoord* VertexTextureBuffer;
	texBuf->Lock(0, 0, (void**)&VertexTextureBuffer, 0);

	for (uint t = 0; t < h.numTris; ++t)
	{
		for (uint i = 0; i < 3; ++i)
		{
			VertexTextureBuffer[TriangleBuffer[t].vertInd[i]].s = (float)CoordBuffer[TriangleBuffer[t].texInd[i]].s / h.skinWidth;
			VertexTextureBuffer[TriangleBuffer[t].vertInd[i]].t = (float)CoordBuffer[TriangleBuffer[t].texInd[i]].t / h.skinHeight;
		}
	}

	texBuf->Unlock();

	delete[] CoordBuffer;
	delete[] TriangleBuffer;

	f.close();

	if (normals)
	{
		D3DVERTEXELEMENT9 elem[] =
		{
			{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
			{1, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1},
			{1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   1},
			{2, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};

		HRESULT res = mamain->d3ddev->CreateVertexDeclaration(elem, &decl);

		if (FAILED(res))
		{
			mamain->err.onErrorDX9("Failed to create vertex declaration", res);
			return 0;
		}
	}
	else
	{
		D3DVERTEXELEMENT9 elem[] =
		{
			{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1},
			{2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};

		HRESULT res = mamain->d3ddev->CreateVertexDeclaration(elem, &decl);

		if (FAILED(res))
		{
			mamain->err.onErrorDX9("Failed to create vertex declaration", res);
			return 0;
		}
	}

	return 1;
}

void MD2Model::setTexture(LPDIRECT3DTEXTURE9 tex)
{
	if (this->tex != 0)
		this->tex->Release();

	tex->AddRef();
	this->tex = tex;
}

uint MD2Model::getFrameCount()
{
	return vertBufs.size();
}

void MD2Model::render(uint frame1, uint frame2, float tween)
{
	mamain->d3ddev->SetTexture(0, tex);

	mamain->d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	mamain->d3ddev->SetRenderState(D3DRS_TWEENFACTOR, *(DWORD*) &tween);
	mamain->d3ddev->SetVertexDeclaration(decl);

	mamain->d3ddev->SetIndices(indBuf);
	mamain->d3ddev->SetStreamSource(0, vertBufs[clamp(frame1, 0u, vertBufs.size())], 0, normals ? sizeof(VertNorm) : sizeof(Vertex));
	mamain->d3ddev->SetStreamSource(1, vertBufs[clamp(frame2, 0u, vertBufs.size())], 0, normals ? sizeof(VertNorm) : sizeof(Vertex));
	mamain->d3ddev->SetStreamSource(2, texBuf, 0, sizeof(TexCoord));

	mamain->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertCount, 0, triCount);

	mamain->d3ddev->SetVertexDeclaration(NULL);
	mamain->d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
}

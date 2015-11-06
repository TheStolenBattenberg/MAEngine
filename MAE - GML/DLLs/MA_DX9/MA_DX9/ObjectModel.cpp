#include "Main.h"

/**
 * MD2 Model
 */
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
}

bool MD2Model::load(std::string model)
{
	std::ifstream f(model, std::ios::in | std::ios::binary);
		
	if (!f.is_open())
	{
		mamain.err.onError("Failed to open MD2 file.");
		return 0;
	}

	/**
	 * Load and validate MD2 Header
	 */

	MD2Type::Header h;

	f.read((char*) &h, sizeof(h));

	if (h.magicNumber != MD2_MAGICNUMBER || h.version != MD2_VERSION || h.frameSize == 0)
	{
		mamain.err.onError("The MD2 header is corrupt.");
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
	f.read((char*) FrameBuffer, h.frameSize * h.numFrames);

	MD2Type::Frame* CurrentFrame;

	for (uint frame = 0; frame < h.numFrames; ++frame)
	{
		CurrentFrame = (MD2Type::Frame*) &FrameBuffer[h.frameSize * frame];

		LPDIRECT3DVERTEXBUFFER9 vb;

		HRESULT result = mamain.d3ddev->CreateVertexBuffer(h.numVert * sizeof(Vertex), 0, 0, D3DPOOL_DEFAULT, &vb, 0);

		if (FAILED(result))
		{
			mamain.err.onErrorDX9("Couldn't create the DirectX9 Vertex Buffer!", result);

			delete[] FrameBuffer;

			return 0;
		}

		Vertex* Vertices;
		vb->Lock(0, 0, (void**) &Vertices, 0);

		for (uint vert = 0; vert < h.numVert; ++vert)
			for (uint i = 0; i < 3; i++)
				(&Vertices[vert].x)[i] = (CurrentFrame->verticies[vert].vertex[i] * CurrentFrame->scale[i]) + CurrentFrame->translate[i];

		vb->Unlock();

		vertBufs.push_back(vb);
	}

	delete[] FrameBuffer;

	/**
	 * Load triangle data
	 */

	MD2Type::Triangle* TriangleBuffer = new MD2Type::Triangle[h.numTris];

	f.seekg(h.ofsTris, std::ios::beg);
	f.read((char*) TriangleBuffer, h.numTris * sizeof(*TriangleBuffer));

	/**
	 * Load index data
	 */

	HRESULT result = mamain.d3ddev->CreateIndexBuffer(h.numTris * sizeof(MD2Type::IndexBuffer), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indBuf, 0);

	if (FAILED(result))
	{
		mamain.err.onErrorDX9("Couldn't create the DirectX9 Index Buffer!", result);

		delete[] TriangleBuffer;

		return 0;
	}

	MD2Type::IndexBuffer* IndexBuffer;
	indBuf->Lock(0, 0, (void**) &IndexBuffer, 0);

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
	f.read((char*) CoordBuffer, h.numST * sizeof(*CoordBuffer));

	result = mamain.d3ddev->CreateVertexBuffer(h.numVert * sizeof(TexCoord), 0, 0, D3DPOOL_DEFAULT, &texBuf, 0);

	if (FAILED(result))
	{
		mamain.err.onErrorDX9("Couldn't create the DirectX9 Vertex Buffer!", result);

		delete[] CoordBuffer;
		delete[] TriangleBuffer;

		return 0;
	}

	TexCoord* VertexTextureBuffer;
	texBuf->Lock(0, 0, (void**) &VertexTextureBuffer, 0);

	for (uint t = 0; t < h.numTris; ++t)
	{
		for (uint i = 0; i < 3; ++i)
		{
			VertexTextureBuffer[TriangleBuffer[t].vertInd[i]].s = (float) CoordBuffer[TriangleBuffer[t].texInd[i]].s / h.skinWidth;
			VertexTextureBuffer[TriangleBuffer[t].vertInd[i]].t = (float) CoordBuffer[TriangleBuffer[t].texInd[i]].t / h.skinHeight;
		}
	}

	texBuf->Unlock();

	delete[] CoordBuffer;
	delete[] TriangleBuffer;

	f.close();

	return 1;
}

void MD2Model::setTexture(LPDIRECT3DTEXTURE9 tex)
{
	if (this->tex != 0)
		this->tex->Release();

	tex->AddRef();
	this->tex = tex;
}

LPDIRECT3DVERTEXBUFFER9 MD2Model::getVB(uint frame)
{
	return vertBufs[frame];
}

LPDIRECT3DVERTEXBUFFER9 MD2Model::getTB()
{
	return texBuf;
}

LPDIRECT3DINDEXBUFFER9 MD2Model::getIB()
{
	return indBuf;
}

IDirect3DTexture9* MD2Model::getTex()
{
	return tex;
}

uint MD2Model::getVertCount()
{
	return vertCount;
}

uint MD2Model::getTriCount()
{
	return triCount;
}

uint MD2Model::getFrameCount()
{
	return vertBufs.size();
}

/**
 * MSM Model
 */
MSMModel::~MSMModel()
{
	for (uint i = 0; i < meshCount; ++i)
	{
		if (meshBuf[i] != 0)
			meshBuf[i]->Release();

		if (indBuf[i] != 0)
			indBuf[i]->Release();

		if (tex[i] != 0)
			tex[i]->Release();
	}
}

bool MSMModel::load(std::string model)
{
	std::ifstream f(model, std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		mamain.err.onError("Failed to open MSM file.");
		return 0;
	}

	/**
	 * Load and validate MSM Header.
	 */
	MSMType::Header h;

	f.read((char*)&h, sizeof(h));

	if (h.magicNumber != MSM_MAGICNUMBER || h.Version != MSM_VERSION || h.MeshCount == 0)
	{
		mamain.err.onError("The MSM Header is corrupt.");
		return 0;
	}

	meshCount = h.MeshCount;
	vertCount.reserve(meshCount);
	triCount.reserve(meshCount);
	hasShader.reserve(meshCount);
	meshBuf.reserve(meshCount);
	indBuf.reserve(meshCount);
	tex.reserve(meshCount);
	mat.reserve(meshCount);


	/**
	 * Load MSM Meshs.
	 */
	HRESULT result;

	for (uint i = 0; i < meshCount; ++i)
	{
		f.read((char*)&vertCount[i], sizeof(ushort));
		f.read((char*)&triCount[i], sizeof(ushort));
		f.read((char*)&hasShader[i], sizeof(byte));


		/**
		 * Load MSM Vertices.
		 */
		result = mamain.d3ddev->CreateVertexBuffer(vertCount[i] * sizeof(MSMType::Vertex), 0, 0, D3DPOOL_DEFAULT, &meshBuf[i], 0);
		if (FAILED(result))
		{
			mamain.err.onErrorDX9("Couldn't create the DirectX9 Vertex Buffer!", result);
			return 0;
		}

		MSMType::Vertex* Vertices;

		meshBuf[i]->Lock(0, 0, (void**) &Vertices, 0);
			f.read((char*)&Vertices, sizeof(MSMType::Vertex) * vertCount[i]);
		meshBuf[i]->Unlock();

		delete[] Vertices;

		/**
		 * Load MSM Indices
		 */
		result = mamain.d3ddev->CreateIndexBuffer(triCount[i] * sizeof(MSMType::Triangle), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indBuf[i], 0);
		if (FAILED(result))
		{
			mamain.err.onErrorDX9("Couldn't create the DirectX9 Index Buffer!", result);
			return 0;
		}

		MSMType::Triangle* Index;

		indBuf[i]->Lock(0, 0, (void**)&Index, 0);
			f.read((char*)&Index, sizeof(MSMType::Triangle) * triCount[i]);
		indBuf[i]->Unlock();

		delete[] Index;

		/**
		 * Load MSM Material
		 */
		f.read((char*)&mat[i].Diffuse, sizeof(float)*4);
		f.read((char*)&mat[i].Ambient, sizeof(float)*4);
		f.read((char*)&mat[i].Specular, sizeof(float)*4);
		f.read((char*)&mat[i].Emissive, sizeof(float)*4);
		f.read((char*)&mat[i].Power, sizeof(float));

		/**
		* Load MSM Shader.
		*/
		if (hasShader[i] == 1)
		{
			ushort* VShaderLength;
			f.read((char*)&VShaderLength, sizeof(ushort));
			// Read VShaderCode

			ushort* PShaderLength;
			f.read((char*)&PShaderLength, sizeof(ushort));
			// Read PShaderCode
		}
	}

	f.close();

	return 1;
}

void MSMModel::setTexture(LPDIRECT3DTEXTURE9 tex, uint mesh)
{
	if (this->tex[mesh] != 0)
		this->tex[mesh]->Release();

	tex->AddRef();
	this->tex[mesh] = tex;
}

LPDIRECT3DVERTEXBUFFER9 MSMModel::getMesh(uint mesh)
{
	return meshBuf[mesh];
}

LPDIRECT3DINDEXBUFFER9 MSMModel::getIB(uint mesh)
{
	return indBuf[mesh];
}

IDirect3DTexture9* MSMModel::getTex(uint mesh)
{
	return tex[mesh];
}

D3DMATERIAL9 MSMModel::getMat(uint mesh)
{
	return mat[mesh];
}

uint MSMModel::getTriCount(uint mesh)
{
	return triCount[mesh];
}

uint MSMModel::getVertCount(uint mesh)
{
	return vertCount[mesh];
}

uint MSMModel::getMeshCount()
{
	return meshCount;
}
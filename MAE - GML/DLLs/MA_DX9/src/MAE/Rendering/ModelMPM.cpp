#include <MAE/Rendering/ModelMPM.h>

#include <MAE/Core/Utils.h>
#include <MAE/Main.h>
#include <MAE/Core/Utils.h>

#include <MAE/GMLAPI/GMLMain.h>

#include <fstream>

MPMModel::~MPMModel()
{
	for (auto i : meshes)
	{
		if (i.decl != 0)
			i.decl->Release();
		
		if (i.vb != 0)
			i.vb->Release();

		if (i.ib != 0)
			i.ib->Release();
	}

	meshes.clear();
	instances.clear();
}

ErrorCode MPMModel::load(const std::string& model)
{
	std::ifstream f(model, std::ios::in | std::ios::binary);

	MPM::Header h;
	
	if (!ReadFromFile(f, h))
		return ErrorReadFile;

	if (h.magicNumber != MPM::MagicNumber)
		return ErrorReadFile;

	if (h.compVersion > MPM::Version)
		return ErrorReadFile;

	for (uint i = 0; i < h.numMeshes; ++i)
		meshes.push_back({0, 0, 0, 0, 0, 0, 0});

	MPM::PacketHeader ph;

	if (!ReadFromFile(f, ph))
		return ErrorReadFile;

	while (ph.id != MPM::PacketEndOfFileID)
	{
		auto offs = f.tellg();

		ErrorCode err = ErrorOk;

		switch (ph.id)
		{
		case MPM::PacketInstID:
			err = readInstances(f);
			break;
		case MPM::PacketMeshID:
			err = readMesh(f);
			break;
		case MPM::PacketVertexDescID:
			err = readVertexDesc(f);
			break;
		case MPM::PacketVertexDataID:
			err = readVertexData(f);
			break;
		case MPM::PacketVertexIndexDataID:
			err = readIndexData(f);
			break;
		default:
			f.seekg(ph.length, std::ios_base::cur);
		}

		if (err != ErrorOk)
			return err;

		if (f.tellg() - offs != ph.length)
			return ErrorReadFile;

		if (!ReadFromFile(f, ph))
			return ErrorReadFile;
	}

	return ErrorOk;
}

ErrorCode MPMModel::readInstances(std::ifstream& f)
{
	MPM::InstHeader ih;

	if (!ReadFromFile(f, ih))
		return ErrorReadFile;

	std::vector<MPM::Inst> inst;

	inst.reserve(ih.num);

	for (uint i = 0; i < ih.num; ++i)
	{
		MPM::Inst in;

		if (!ReadFromFile(f, in))
			return ErrorReadFile;

		inst.push_back(in);
	}

	instances.reserve(ih.num);

	for (auto i : inst)
		instances.push_back({i.meshInd, mat4::compose(i.scal, i.rot, i.trans)});

	return ErrorOk;
}

ErrorCode MPMModel::readMesh(std::ifstream& f)
{
	MPM::Mesh mesh;

	if (!ReadFromFile(f, mesh))
		return ErrorReadFile;

	meshes[mesh.meshId].matInd      = mesh.matInd;
	meshes[mesh.meshId].numPrim     = (mesh.numIndices == 0 ? mesh.numVertices : mesh.numIndices) / 3;
	meshes[mesh.meshId].numVertices = mesh.numVertices;

	return ErrorOk;
}

ErrorCode MPMModel::readVertexDesc(std::ifstream& f)
{
	MPM::PacketVertexDescHeader vh;

	if (!ReadFromFile(f, vh))
		return ErrorReadFile;

	meshes[vh.meshInd].stride = vh.vertStride;

	std::vector<MPM::PacketVertexDesc> vertexDescs;

	vertexDescs.reserve(vh.num);

	for (uint i = 0; i < vh.num; ++i)
	{
		MPM::PacketVertexDesc vd;

		if (!ReadFromFile(f, vd))
			return ErrorReadFile;

		vertexDescs.push_back(vd);
	}

	std::vector<D3DVERTEXELEMENT9> elements;
	elements.reserve(vh.num + 1);

	BYTE typeTable[] = {
		D3DDECLTYPE_UNUSED,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT4,
		D3DDECLTYPE_D3DCOLOR,
		D3DDECLTYPE_UBYTE4,
		D3DDECLTYPE_SHORT2,
		D3DDECLTYPE_SHORT4
	};

	BYTE usageTable[] = {
		D3DDECLUSAGE_POSITION,
		D3DDECLUSAGE_POSITION,
		D3DDECLUSAGE_NORMAL,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_COLOR
	};

	for (auto i : vertexDescs)
		elements.push_back({0, i.offset, typeTable[i.type], 0, usageTable[i.usage], 0});

	elements.push_back(D3DDECL_END());

	HRESULT res = mamain->d3ddev->CreateVertexDeclaration(elements.data(), &meshes[vh.meshInd].decl);

	if (FAILED(res))
		return mamain->setError(ErrorCreateVertexDecl);
	
	return ErrorOk;
}

ErrorCode MPMModel::readVertexData(std::ifstream& f)
{
	MPM::PacketVertexDataHeader vdh;

	if (!ReadFromFile(f, vdh))
		return ErrorReadFile;

	LPDIRECT3DVERTEXBUFFER9 vb;

	HRESULT res = mamain->d3ddev->CreateVertexBuffer(vdh.length, 0, 0, D3DPOOL_DEFAULT, &vb, 0);

	if (FAILED(res))
		return mamain->setError(ErrorCreateVertexBuffer);

	void* data;

	vb->Lock(0, 0, &data, 0);

	f.read((char*) data, vdh.length);

	vb->Unlock();

	meshes[vdh.meshInd].vb = vb;

	return ErrorOk;
}

ErrorCode MPMModel::readIndexData(std::ifstream& f)
{
	MPM::PacketVertexIndexHeader vih;

	if (!ReadFromFile(f, vih))
		return ErrorReadFile;

	uint length = vih.num * (vih.type == vih.TypeU32 ? sizeof(uint) : sizeof(ushort));

	LPDIRECT3DINDEXBUFFER9 ib;

	HRESULT res = mamain->d3ddev->CreateIndexBuffer(length, 0, vih.type == vih.TypeU32 ? D3DFMT_INDEX32 : D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0);

	if (FAILED(res))
		return mamain->setError(ErrorCreateIndexBuffer);

	void* data;

	ib->Lock(0, 0, &data, 0);

	f.read((char*) data, length);

	ib->Unlock();

	meshes[vih.meshInd].ib = ib;

	return ErrorOk;
}

void MPMModel::render()
{
	for (auto i : instances)
	{
		Mesh& mesh = meshes[i.meshInd];

		mamain->d3ddev->SetTransform(D3DTS_WORLDMATRIX(1), (D3DMATRIX*) &i.transform.data);

		mamain->d3ddev->SetVertexDeclaration(mesh.decl);
		mamain->d3ddev->SetStreamSource(0, mesh.vb, 0, mesh.stride);

		if (mesh.ib == 0)
			mamain->d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, mesh.numPrim);
		else
		{
			mamain->d3ddev->SetIndices(mesh.ib);
			mamain->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.numVertices, 0, mesh.numPrim);
		}
	}

	mat4 m;
	mamain->d3ddev->SetTransform(D3DTS_WORLDMATRIX(1), (D3DMATRIX*) &m.data);
}

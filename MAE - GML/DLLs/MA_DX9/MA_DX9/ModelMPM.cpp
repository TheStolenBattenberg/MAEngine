#include "ModelMPM.h"

#include "Utils.h"
#include "Main.h"

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

bool MPMModel::load(const std::string& model)
{
	std::ifstream f(model, std::ios::in | std::ios::binary);

	auto h = ReadFromFile<MPMTypes::Header>(f);

	if (h.magicNumber != MPMTypes::MagicNumber)
		return 0;

	if (h.compVersion > MPMTypes::Version)
		return 0;

	for (uint i = 0; i < h.numMeshes; ++i)
		meshes.push_back(Mesh());

	// TODO: Check if it's necassary
	memset(meshes.data(), 0, meshes.size() * sizeof(Mesh));

	auto ph = ReadFromFile<MPMTypes::PacketHeader>(f);

	while (ph.id != MPMTypes::PacketEndOfFileID)
	{
		auto offs = f.tellg();

		switch (ph.id)
		{
		case MPMTypes::PacketInstID:
			readInstances(f);
			break;
		case MPMTypes::PacketMeshID:
			readMesh(f);
			break;
		case MPMTypes::PacketVertexDescID:
			readVertexDesc(f);
			break;
		case MPMTypes::PacketVertexDataID:
			readVertexData(f);
			break;
		case MPMTypes::PacketVertexIndexDataID:
			readIndexData(f);
			break;
		default:
			f.seekg(ph.length, std::ios_base::cur);
		}

		if (f.tellg() - offs != ph.length)
			return 0;

		ph = ReadFromFile<MPMTypes::PacketHeader>(f);
	}

	return 1;
}

void MPMModel::readInstances(std::ifstream& f)
{
	auto ih = ReadFromFile<MPMTypes::InstHeader>(f);

	std::vector<MPMTypes::Inst> inst;

	ReadVectorFromFile(f, inst, ih.num);

	instances.reserve(ih.num);

	for (auto i : inst)
		instances.push_back({i.meshInd, mat4::compose(i.scal, i.rot, i.trans)});
}

void MPMModel::readMesh(std::ifstream& f)
{
	auto mesh = ReadFromFile<MPMTypes::Mesh>(f);

	meshes[mesh.meshId].matInd      = mesh.matInd;
	meshes[mesh.meshId].numPrim     = (mesh.numIndices == 0 ? mesh.numVertices : mesh.numIndices) / 3;
	meshes[mesh.meshId].numVertices = mesh.numVertices;
}

void MPMModel::readVertexDesc(std::ifstream& f)
{
	auto vh = ReadFromFile<MPMTypes::PacketVertexDescHeader>(f);

	meshes[vh.meshInd].stride = vh.vertStride;

	std::vector<MPMTypes::PacketVertexDesc> vertexDescs;
	ReadVectorFromFile(f, vertexDescs, vh.num);

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

	// TODO: Add error checking
	mamain->d3ddev->CreateVertexDeclaration(elements.data(), &meshes[vh.meshInd].decl);
}

void MPMModel::readVertexData(std::ifstream& f)
{
	auto vdh = ReadFromFile<MPMTypes::PacketVertexDataHeader>(f);

	LPDIRECT3DVERTEXBUFFER9 vb;

	// TODO: Add error checking
	mamain->d3ddev->CreateVertexBuffer(vdh.length, 0, 0, D3DPOOL_DEFAULT, &vb, 0);

	void* data;

	vb->Lock(0, 0, &data, 0);

	f.read((char*) data, vdh.length);

	vb->Unlock();

	meshes[vdh.meshInd].vb = vb;
}

void MPMModel::readIndexData(std::ifstream& f)
{
	auto vih = ReadFromFile<MPMTypes::PacketVertexIndexHeader>(f);

	uint length = vih.num * (vih.type == vih.TypeU32 ? sizeof(uint) : sizeof(ushort));

	LPDIRECT3DINDEXBUFFER9 ib;

	// TODO: Add error checking
	mamain->d3ddev->CreateIndexBuffer(length, 0, vih.type == vih.TypeU32 ? D3DFMT_INDEX32 : D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0);

	void* data;

	ib->Lock(0, 0, &data, 0);

	f.read((char*) data, length);

	ib->Unlock();

	meshes[vih.meshInd].ib = ib;
}

void MPMModel::render()
{
	for (auto i : instances)
	{
		Mesh& mesh = meshes[i.meshInd];

		mamain->d3ddev->SetTransform(D3DTS_WORLDMATRIX(0), (D3DMATRIX*) &i.transform.data);

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
}

#include <MAE/Rendering/Model/ModelMPM.h>

#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Model/ModelDraft.h>
#include <MAE/Rendering/VertexData.h>
#include <MAE/Rendering/Renderer.h>
#include <MAE/Core/Exception.h>

ModelDraft* MPMModel::load(const char* model) {
	std::ifstream f(model, std::ios::in | std::ios::binary);

	MPM::Header h;
	
	if (!readFromStream(f, h))
		throw Exception("Failed to read from file");

	if (h.magicNumber != MPM::MagicNumber)
		throw Exception("Invalid header");

	if (h.compVersion > MPM::Version)
		throw Exception("Invalid header");

	MPM::PacketHeader ph;

	if (!readFromStream(f, ph))
		throw Exception("Failed to read from file");

	DynamicArray<ModelDraft::Mesh> meshes(h.numMeshes);
	DynamicArray<ModelDraft::Inst> instances;
	DynamicArray<ModelDraft::Material> materials(h.numMaterials);

	while (ph.id != MPM::PacketEndOfFileID) {
		auto offs = f.tellg();

		switch (ph.id) {
		case MPM::PacketInstID:
			readInstances(instances, f);
			break;
		case MPM::PacketMaterialID:
			readMaterials(materials, f);
			break;
		case MPM::PacketMeshID:
			readMesh(meshes, f);
			break;
		case MPM::PacketVertexDescID:
			readVertexDesc(meshes, f);
			break;
		case MPM::PacketVertexDataID:
			readVertexData(meshes, f);
			break;
		case MPM::PacketVertexIndexDataID:
			readIndexData(meshes, f);
			break;
		default:
			f.seekg(ph.length, std::ios_base::cur);
		}

		if (f.tellg() - offs != ph.length || !readFromStream(f, ph))
			throw Exception("Failed to read from file");
	}

	return new ModelDraft(std::move(meshes), std::move(instances), std::move(materials));
}

void MPMModel::readInstances(DynamicArray<ModelDraft::Inst>& inst, std::ifstream& f) {
	MPM::InstHeader ih;

	if (!readFromStream(f, ih))
		throw Exception("Failed to read from file");

	inst.size(ih.num);

	for (auto& instance : inst) {
		MPM::Inst in;

		if (!readFromStream(f, in))
			throw Exception("Failed to read from file");

		instance = { in.meshInd, mat4::compose(in.scal, in.rot, in.trans) };
	}
}

void MPMModel::readMaterials(DynamicArray<ModelDraft::Material>& materials, std::ifstream& f) {
	MPM::MaterialHeader mh;

	if (!readFromStream(f, mh))
		throw Exception("Failed to read from file");

	materials.size(mh.num);

	for (auto& m : materials) {
		MPM::Material mat;

		if (!readFromStream(f, mat))
			throw Exception("Failed to read from file");

		m.m_tex = mat.tex;
	}
}

void MPMModel::readMesh(DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f) {
	MPM::Mesh mesh;

	if (!readFromStream(f, mesh))
		throw Exception("Failed to read from file");

	meshes[mesh.meshId].m_matInd = mesh.matInd;
	meshes[mesh.meshId].m_numPrim = (mesh.numIndices == 0 ? mesh.numVertices : mesh.numIndices) / 3;
}

void MPMModel::readVertexDesc(DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f) {
	MPM::PacketVertexDescHeader vh;

	if (!readFromStream(f, vh))
		throw Exception("Failed to read from file");

	auto& mesh = meshes[vh.meshInd];

	mesh.m_elements.size(vh.num);
	mesh.m_stride = vh.vertStride;

	for (auto& element : mesh.m_elements) {
		const uint tableUsage[] = {
			0,
			ModelDraft::Element::UsagePosition,
			ModelDraft::Element::UsageNormal,
			ModelDraft::Element::UsageTexCoord,
			ModelDraft::Element::UsageColor
		};

		const uint tableType[] = {
			0,
			VertexData::TypeFloat,
			VertexData::TypeVec2,
			VertexData::TypeVec3,
			VertexData::TypeVec4
		};

		MPM::PacketVertexDesc desc;

		if (!readFromStream(f, desc))
			throw Exception("Failed to read from file");

		if (desc.usage < 1 || desc.usage >= sizeof(tableUsage) || desc.type < 1 || desc.type >= sizeof(tableType))
			throw Exception("Failed to read from file");

		element = { tableUsage[desc.usage], desc.offset, tableType[desc.type] };
	}
}

void MPMModel::readVertexData(DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f) {
	MPM::PacketVertexDataHeader vdh;

	if (!readFromStream(f, vdh))
		throw Exception("Failed to read from file");

	meshes[vdh.meshInd].m_vb.size(vdh.length);
	f.read((char*) meshes[vdh.meshInd].m_vb.data(), vdh.length);
}

void MPMModel::readIndexData(DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f) {
	const uint tableType[] = {
		0,
		Renderer::IndexBuffer16,
		Renderer::IndexBuffer32
	};
	
	MPM::PacketVertexIndexHeader vih;

	if (!readFromStream(f, vih))
		throw Exception("Failed to read from file");

	if (vih.type < 1 || vih.type >= sizeof(tableType))
		throw Exception("Failed to read from file");

	auto length = vih.num * (vih.type == vih.TypeU32 ? sizeof(uint) : sizeof(ushort));

	meshes[vih.meshInd].m_ibType = tableType[vih.type];
	meshes[vih.meshInd].m_ib.size(length);
	f.read((char*) meshes[vih.meshInd].m_ib.data(), length);
}

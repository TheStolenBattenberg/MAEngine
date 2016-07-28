#pragma once

#include <MAE/Core/Color.h>
#include <MAE/Core/DynamicArray.h>
#include <MAE/Core/Mat.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Vec.h>

#include <memory>
#include <vector>

class ModelDraft {
public:
	struct Material {
		std::string m_tex;
	};

	struct Element {
		enum {
			UsagePosition,
			UsageNormal,
			UsageTexCoord,
			UsageColor
		};

		uint m_usage;
		uint m_offset;
		uint m_type;
	};

	struct Mesh {
		uint m_matInd;
		uint m_numPrim;
		uint m_stride;
		uint m_ibType;

		DynamicArray<Element> m_elements;
		DynamicArray<ubyte>   m_vb;
		DynamicArray<ubyte>   m_ib;
	};

	struct Inst {
		uint m_meshInd;
		mat4 m_transform;
	};

	ModelDraft(DynamicArray<Mesh>&& meshes, DynamicArray<Inst>&& inst, DynamicArray<Material>&& mat):
		m_meshes(std::move(meshes)), m_instances(std::move(inst)), m_materials(std::move(mat)) { }

	inline const auto& getMeshes() const {
		return m_meshes;
	}

	inline const auto& getInstances() const {
		return m_instances;
	}

	inline const auto& getMaterials() const {
		return m_materials;
	}

private:
	DynamicArray<Mesh>     m_meshes;
	DynamicArray<Inst>     m_instances;
	DynamicArray<Material> m_materials;
};

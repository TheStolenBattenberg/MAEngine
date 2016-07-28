#pragma once

#include <MAE/Core/DynamicArray.h>
#include <MAE/Core/Mat.h>
#include <MAE/Rendering/Buffer/IndexBuffer.h>
#include <MAE/Rendering/Buffer/VertexBuffer.h>
#include <MAE/Rendering/Model/ModelBase.h>
#include <MAE/Rendering/Model/ModelDraft.h>
#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Rendering/TextureCollection.h>
#include <MAE/Rendering/VertexData.h>

#include <cassert>

class ForwardPipelineShader {
public:
	enum {
		LocationPos  = 0,
		LocationNorm = 1,
		LocationTex  = 2
	};

	ForwardPipelineShader(Renderer* renderer);
	~ForwardPipelineShader();

	uint getLocation(uint loc);

protected:
	Shader* m_shader;

	uint m_uMVP;
	uint m_uNormal;
	uint m_uAmbientColor;
	uint m_uLightDir;
	uint m_uTex;
};

class ForwardPipeline: ForwardPipelineShader {
private:
	class Model: public ModelBase {
	public:
		struct Material {
			Texture* m_tex;
		};

		struct Mesh {
			uint m_numPrim;

			Material*     m_mat;
			VertexData*   m_vd;
			VertexBuffer* m_vb;
			IndexBuffer*  m_ib;
		};

		struct Instance {
			Mesh* m_mesh;
			mat4 m_trans;
		};

		Model(DynamicArray<Mesh>&& meshes, DynamicArray<Instance>&& inst, DynamicArray<Material>&& mat):
			m_meshes(std::move(meshes)), m_instances(std::move(inst)), m_materials(std::move(mat)) { }

		~Model() {
			for (auto& mesh : m_meshes) {
				delete mesh.m_vd;
				delete mesh.m_vb;
				delete mesh.m_ib;
			}
		}

		inline const auto& getInstances() const {
			return m_instances;
		}

	private:
		DynamicArray<Material> m_materials;
		DynamicArray<Mesh> m_meshes;
		DynamicArray<Instance> m_instances;
	};

public:
	ForwardPipeline(Renderer* renderer): ForwardPipelineShader(renderer), m_renderer(renderer) { }

	ModelBase* createModel(const ModelDraft* draft, TextureCollectionBase& dir) {
		auto& draftMaterials = draft->getMaterials();
		auto& draftMeshes    = draft->getMeshes();
		auto& draftInstances = draft->getInstances();

		DynamicArray<Model::Material> materials(draftMaterials.size());

		for (uint i = 0; i < draftMaterials.size(); ++i)
			materials[i] = { dir.findTexture(draftMaterials[i].m_tex) };

		DynamicArray<Model::Mesh> meshes(draftMeshes.size());

		for (uint i = 0; i < draftMeshes.size(); ++i) {
			auto& mesh = draftMeshes[i];

			auto vb = m_renderer->createVertexBuffer(mesh.m_vb.size(), mesh.m_vb.data());
			auto vd = m_renderer->createVertexData();

			IndexBuffer* ib = nullptr;

			if (!mesh.m_ib.empty())
				vd->setIndexBuffer(ib = m_renderer->createIndexBuffer(mesh.m_ib.size(), mesh.m_ibType, mesh.m_ib.data()));

			DynamicArray<VertexData::Element> elements(mesh.m_elements.size());

			for (uint j = 0; j < mesh.m_elements.size(); ++j) {
				const uint locTable[] = {
					LocationPos,
					LocationNorm,
					LocationTex
				};

				assert(("Invalid location", mesh.m_elements[j].m_usage < sizeof(locTable) / sizeof(uint)));
				elements[j] = { getLocation(locTable[mesh.m_elements[j].m_usage]), mesh.m_elements[j].m_type, mesh.m_elements[j].m_offset };
			}

			vd->addVertexBuffer(vb, mesh.m_stride, 0, elements.size(), elements.data());
			vd->build();

			meshes[i] = { mesh.m_numPrim, &materials[mesh.m_matInd], vd, vb, ib };
		}

		DynamicArray<Model::Instance> instances(draftInstances.size());

		for (uint i = 0; i < draftInstances.size(); ++i)
			instances[i] = { &meshes[draftInstances[i].m_meshInd], draftInstances[i].m_transform };

		return new Model(std::move(meshes), std::move(instances), std::move(materials));
	}

	void renderModel(ModelBase* model) {
		auto m = (Model*) model;

		m_renderer->setShader(m_shader);

		for (auto& inst : m->getInstances()) {
			auto& mesh = *inst.m_mesh;

			m_shader->setSampler(m_uTex, mesh.m_mat->m_tex);
			m_shader->setMat4(m_uMVP, m_mvp);
			m_shader->setMat3(m_uNormal, m_normal);
			m_shader->setVec3(m_uLightDir, vec3(0.577f, 0.577f, 0.577f));
			m_shader->setVec4(m_uAmbientColor, vec4(0.2f, 0.2f, 0.2f, 0.0f));

			if (mesh.m_ib == nullptr)
				m_renderer->draw(mesh.m_vd, Renderer::PrimitveTypeTriangleList, 0, mesh.m_numPrim);
			else
				m_renderer->drawIndexed(mesh.m_vd, Renderer::PrimitveTypeTriangleList, mesh.m_numPrim);
		}

		m_shader->setSampler(m_uTex, nullptr);
	}

	void setMVP(const mat4& mvp) {
		m_mvp = mvp;
	}

	void setNormal(const mat3& normal) {
		m_normal = normal;
	}

private:
	Renderer* m_renderer;

	mat4 m_mvp;
	mat3 m_normal;
};

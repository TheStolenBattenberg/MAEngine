#include <iostream>

#include <MAE/Main.h>
#include <MAE/Rendering/ParticleSystem.h>
#include <MAE/Main.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Rendering/RendererImpl.h>

ParticleSystem::ParticleSystem(Renderer* renderer): renderer(renderer) {
	D3DVERTEXELEMENT9 part_decl_ve[] = {
		{ 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
		{ 0, 28, D3DDECLTYPE_FLOAT1,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE,    0 },
		D3DDECL_END()
	};

	auto device = ((RendererImpl*) renderer)->getDevice();

	device->CreateVertexDeclaration(part_decl_ve, &decl);

	HRESULT res = device->CreateVertexBuffer(sizeof(ParticlePoint), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &psVertexBuffer, 0);

	// TODO: Add proper error checking
}

ParticleSystem::~ParticleSystem() {
	if (psEmitter != nullptr) {
		delete psEmitter;
	}

	if (psVertexBuffer != 0) {
		psVertexBuffer->Release();
	}

	if (decl != nullptr)
		decl->Release();

	psBuffer.clear();
}

void ParticleSystem::createEmitter() {
	/**
	 * This needs to be changed. We should have multiple emitter shapes, like sphere, box, cylinder etc.
	 */
	psEmitter = new ParticleEmitter(PE_BOX);
}

ParticleEmitter* ParticleSystem::getEmitter() {
	return psEmitter;
}

void ParticleSystem::update(uint time) {
	if (psEmitter != nullptr) {
		if (psBuffer.size() < (psMaxParticleCount - psEmitter->getMinEmitt())) {
			uint pC = psEmitter->getSpawnThisTick();

			Particle* parts = new Particle[pC];

			uint partCount = psEmitter->emitt(time, pC, parts);

			if (partCount > 0) {
				for (uint i = 0; i < partCount; ++i) {
					psBuffer.push_back(parts[i]);
				}
			}
			delete[] parts;
		}
	}

	uint i = 0;
	while (i < psBuffer.size()) {
		if (psBuffer[i].pAge > psBuffer[i].pLife)
		{
			psBuffer[i] = psBuffer[psBuffer.size() - 1];
			psBuffer.pop_back();
		}
		else {
			if(psMods.size() > 0) {
				//Run Modifiers.
				for (uint mod = 0; mod < psMods.size(); ++mod) {
					psMods[mod]->update(&psBuffer[i]);
				}
			}
			psBuffer[i].pPosition.x += psBuffer[i].pVelocity.x;
			psBuffer[i].pPosition.y += psBuffer[i].pVelocity.y;
			psBuffer[i].pPosition.z += psBuffer[i].pVelocity.z;
			
			vec3 acc = psEmitter->getAcceleration();
			psBuffer[i].pVelocity.x += acc.x;
			psBuffer[i].pVelocity.y += acc.y;
			psBuffer[i].pVelocity.z += acc.z;

			psBuffer[i].pColour = psEmitter->getColour((float)(psBuffer[i].pAge/4));
			psBuffer[i].pAge++;
			++i;
		}
	}

	if (psBuffer.size() > 0) {
		ParticlePoint* parts;
		psVertexBuffer->Lock(0, 0, (void**)&parts, 0);

		uint i = 0;
		while (i < psBuffer.size()) {

			parts[i].pPosition = psBuffer[i].pPosition;
			parts[i].pColour   = psBuffer[i].pColour;
			parts[i].pSize     = psBuffer[i].pSize;
			++i;
		}

		psVertexBuffer->Unlock();
	}
}

void ParticleSystem::render() {
	auto device = ((RendererImpl*) renderer)->getDevice();

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);

	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	float v;
	v = 0.0f;
	device->SetRenderState(D3DRS_POINTSCALE_A, *(DWORD*)&v);
	device->SetRenderState(D3DRS_POINTSCALE_B, *(DWORD*)&v);
	v = 1.0f;
	device->SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)&v);

	if (texture != 0)
		renderer->setTexture(0, texture);

	device->SetVertexDeclaration(decl);
	device->SetStreamSource(0, psVertexBuffer, 0, sizeof(ParticlePoint));
	device->DrawPrimitive(D3DPT_POINTLIST, 0, psBuffer.size());
	device->SetVertexDeclaration(nullptr);

	device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, false);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

uint ParticleSystem::getParticleCount() {
	return psBuffer.size();
}

void ParticleSystem::setMaxParticleCount(uint max) {
	psMaxParticleCount = max;
	if (psVertexBuffer != 0) {
		psVertexBuffer->Release();
	}
	HRESULT res = ((RendererImpl*) renderer)->getDevice()->CreateVertexBuffer(sizeof(ParticlePoint) * max, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &psVertexBuffer, 0);

	// TODO: Add proper error checking
}

void ParticleSystem::setTexture(Texture* tex) {
	texture = tex;
}

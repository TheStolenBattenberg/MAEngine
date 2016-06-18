#include <iostream>

#include <MAE/Main.h>
#include <MAE/Rendering/ParticleSystem.h>
#include <MAE/Core/Utils.h>
#include <MAE/Main.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <MAE/GMLAPI/GMLMain.h>

ParticleSystem::ParticleSystem() {
	if (mamain->VertexDeclarationParticle == 0) {
		D3DVERTEXELEMENT9 part_decl_ve[] = {
			{ 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
			{ 0, 28, D3DDECLTYPE_FLOAT1,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE,    0 },
			D3DDECL_END()
		};

		mamain->d3ddev->CreateVertexDeclaration(part_decl_ve, &mamain->VertexDeclarationParticle);
	}

	HRESULT res = mamain->d3ddev->CreateVertexBuffer(sizeof(ParticlePoint), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &psVertexBuffer, 0);

	// TODO: Add proper error checking
}

ParticleSystem::~ParticleSystem() {
	if (psEmitter != NULL) {
		delete psEmitter;
	}

	if (psVertexBuffer != 0) {
		psVertexBuffer->Release();
	}

	if (texture != 0)
		texture->release();

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
	if (psEmitter != NULL) {
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
	mamain->d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	mamain->d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mamain->d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	mamain->d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, false);

	mamain->d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	mamain->d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	float v;
	v = psEmitter->getMinSize();
	mamain->d3ddev->SetRenderState(D3DRS_POINTSIZE_MIN, *(DWORD*)&v);
	v = psEmitter->getMaxSize();
	mamain->d3ddev->SetRenderState(D3DRS_POINTSIZE_MAX, *(DWORD*)&v);
	v = 0.0f;
	mamain->d3ddev->SetRenderState(D3DRS_POINTSCALE_A, *(DWORD*)&v);
	mamain->d3ddev->SetRenderState(D3DRS_POINTSCALE_B, *(DWORD*)&v);
	v = 1.0f;
	mamain->d3ddev->SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)&v);

	if (texture != 0)
		mamain->setTexture(0, texture);

	mamain->d3ddev->SetVertexDeclaration(mamain->VertexDeclarationParticle);
	mamain->d3ddev->SetStreamSource(0, psVertexBuffer, 0, sizeof(ParticlePoint));
	mamain->d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, psBuffer.size());
	mamain->d3ddev->SetVertexDeclaration(NULL);

	mamain->d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	mamain->d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, false);

	mamain->d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	mamain->d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	mamain->d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	mamain->d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

uint ParticleSystem::getParticleCount() {
	return psBuffer.size();
}

void ParticleSystem::setMaxParticleCount(uint max) {
	psMaxParticleCount = max;
	if (psVertexBuffer != 0) {
		psVertexBuffer->Release();
	}
	HRESULT res = mamain->d3ddev->CreateVertexBuffer(sizeof(ParticlePoint) * max, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &psVertexBuffer, 0);

	// TODO: Add proper error checking
}

void ParticleSystem::setTexture(Texture* tex) {
	if (texture != 0)
		texture->release();

	tex->addRef();
	texture = tex;
}

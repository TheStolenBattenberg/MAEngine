#include <iostream>

#include "Main.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
	if (mamain->VertexDeclarationParticle == 0) {
		D3DVERTEXELEMENT9 part_decl_ve[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			D3DDECL_END()
		};

		mamain->d3ddev->CreateVertexDeclaration(part_decl_ve, &mamain->VertexDeclarationParticle);
	}

	HRESULT res = mamain->d3ddev->CreateVertexBuffer(sizeof(vec3), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &psVertexBuffer, 0);
	if (FAILED(res)) {
		mamain->err.onErrorDX9("Couldn't create the DirectX9 Vertex Buffer!", res);
	}
}

void ParticleSystem::createEmitter() {
	/**
	 * This needs to be changed. We should have multiple emitter shapes, like sphere, box, cylinder etc.
	 */
	psEmitter = new ParticleEmitter(PE_BOX);
}

void ParticleSystem::createAttractor() {
	psAttractor = new ParticleAttractor();
}

void ParticleSystem::createRepulsor() {
	psRepulsor = new ParticleRepulsor();
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
			if (psAttractor != NULL) {
				//Move the particles towards if in range.
			}

			if (psRepulsor != NULL) {
				//Move the particles away if in range.
			}

			//Normal movement, via velocity.

			//Velocity increase math: POS.X + VEL.X * ACCELERATION.

			//Also do the other particle effects here, such as interp between colours, based on life. Probably a lot more too
			psBuffer[i].pAge++;
			++i;
		}
	}

	if (psBuffer.size() > 0) {
		vec3* parts;
		psVertexBuffer->Lock(0, 0, (void**)&parts, 0);

		uint i = 0;
		while (i < psBuffer.size()) {
			parts[i] = psBuffer[i].pPosition;
			++i;
		}

		psVertexBuffer->Unlock();
	}
}

void ParticleSystem::render() {
	mamain->d3ddev->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)psEmitter->getMinSize());
	mamain->d3ddev->SetRenderState(D3DRS_POINTSIZE_MAX, (DWORD)psEmitter->getMaxSize());
	mamain->d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, true); //Not sure we need to do this every time.
	mamain->d3ddev->SetVertexDeclaration(mamain->VertexDeclarationParticle);
	mamain->d3ddev->SetTexture(0, psTexture);
	mamain->d3ddev->SetStreamSource(0, psVertexBuffer, 0, sizeof(Particle::pPosition));
	mamain->d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, psBuffer.size());
	mamain->d3ddev->SetVertexDeclaration(NULL);
	mamain->d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, false); //This neither.
}

uint ParticleSystem::getParticleCount() {
	return psBuffer.size();
}

void ParticleSystem::setMaxParticleCount(uint max) {
	psMaxParticleCount = max;
}

void ParticleSystem::setTexture(LPDIRECT3DTEXTURE9 tex) {
	if (this->psTexture != 0)
		this->psTexture->Release();

	tex->AddRef();
	this->psTexture = tex;
}

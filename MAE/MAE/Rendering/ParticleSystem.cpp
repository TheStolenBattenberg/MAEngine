#include <iostream>

#include <MAE/Main.h>
#include <MAE/Rendering/RendererImpl.h>
#include <MAE/Rendering/ParticleSystem.h>


ParticleSystem::ParticleSystem(Renderer* renderer) : pRenderer(renderer) {

	D3DVERTEXELEMENT9 partDecl[] = {
		{ 0, 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 28, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
		D3DDECL_END()
	};

	auto device = ((RendererImpl*)pRenderer)->getDevice();
	device->CreateVertexDeclaration(partDecl, &d3dDecl);
	device->CreateVertexBuffer(sizeof(ParticlePoint), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, &d3dVertexBuffer, NULL);
}

ParticleSystem::~ParticleSystem() {
	if (d3dDecl != NULL) {
		d3dDecl->Release();
	}
	if (d3dVertexBuffer != NULL) {
		d3dVertexBuffer->Release();
	}

	vParticles.clear();
	vParticleModifiers.clear();
}

void ParticleSystem::EmitterSet(ParticleEmitter* pe) {
	pEmitter = pe;
}

void ParticleSystem::ModifierAdd(ParticleModifier* mod) {
	vParticleModifiers.push_back(mod);
}

void ParticleSystem::Update(uint time) {
	if (pEmitter != nullptr) {
		if (vParticles.size() < (iMaxParticles - pEmitter->GetMinEmitt())) {
			uint particleCount = irandom_range(pEmitter->GetMinEmitt(), pEmitter->GetMaxEmitt());
			particleCount = pEmitter->Emitt(time, particleCount, vParticles);
		}
	}

	uint i = 0;
	while (i < vParticles.size()) {
		if (vParticles[i].iAge >= vParticles[i].iLife) {
			vParticles[i] = vParticles[vParticles.size() - 1];
			vParticles.pop_back();
		}
		else {
			vParticles[i].vPosition.x += vParticles[i].vVelocity.x;
			vParticles[i].vPosition.y += vParticles[i].vVelocity.y;
			vParticles[i].vPosition.z += vParticles[i].vVelocity.z;

			vec3 Acceleration = pEmitter->GetAcceleration();
			vParticles[i].vVelocity.x += Acceleration.x;
			vParticles[i].vVelocity.y += Acceleration.y;
			vParticles[i].vVelocity.z += Acceleration.z;

			vParticles[i].iAge++;

			for (uint mod = 0; mod < vParticleModifiers.size(); ++mod) {
				vParticles[i] = vParticleModifiers[mod]->Apply(vParticles[i]);
			}
			++i;
		}
	}


	if (vParticles.size() > 0) {
		ParticlePoint* points;
		d3dVertexBuffer->Lock(0, 0, (void**)&points, 0);

		uint i = 0;
		while (i < vParticles.size()) {
			points[i].vPosition = vParticles[i].vPosition;
			points[i].vColour = vParticles[i].vColour;
			points[i].fSize = vParticles[i].fSize;
			++i;
		}
		d3dVertexBuffer->Unlock();
	}
}

void ParticleSystem::Render() {
	auto device = ((RendererImpl*)pRenderer)->getDevice();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);

	float v;
	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	v = 0.0f;
	device->SetRenderState(D3DRS_POINTSCALE_A, *(DWORD*)&v);
	device->SetRenderState(D3DRS_POINTSCALE_B, *(DWORD*)&v);
	v = 1.0f;
	device->SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)&v);
	if (pTexture != nullptr) {
		pRenderer->setTexture(0, pTexture);
	}
	if (d3dDecl != NULL && d3dVertexBuffer != NULL) {
		device->SetVertexDeclaration(d3dDecl);
		device->SetStreamSource(0, d3dVertexBuffer, 0, sizeof(ParticlePoint));
		device->DrawPrimitive(D3DPT_POINTLIST, 0, vParticles.size());
	}

	device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, false);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	device->SetRenderState(D3DRS_ZWRITEENABLE, true);

}

void ParticleSystem::SetTexture(Texture* Tex) {
	pTexture = Tex;
}

void ParticleSystem::SetMaxParticles(uint max) {
	iMaxParticles = max;
	if (d3dVertexBuffer != NULL) {
		d3dVertexBuffer->Release();
	}

	auto device = ((RendererImpl*)pRenderer)->getDevice();
	device->CreateVertexBuffer(sizeof(ParticlePoint) * max, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, &d3dVertexBuffer, NULL);
}

uint ParticleSystem::GetMaxParticles() {
	return iMaxParticles;
}

uint ParticleSystem::GetParticleCount() {
	return vParticles.size();
}
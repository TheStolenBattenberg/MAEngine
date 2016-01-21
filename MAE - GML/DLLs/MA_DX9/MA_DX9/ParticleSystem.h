#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Math.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ParticleModifier.h"

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();

	void createEmitter();
	void createAttractor();
	void createRepulsor();

	ParticleEmitter* getEmitter();

	void update(uint time);
	void render();

	void setTexture(LPDIRECT3DTEXTURE9 tex);

	uint getParticleCount();

	void setMaxParticleCount(uint max);
private:
	std::vector<ParticleModifier*> psMods;
	ParticleEmitter*   psEmitter = NULL;

	std::vector<Particle> psBuffer;

	uint psMaxParticleCount;

	//D3D...
	LPDIRECT3DTEXTURE9 psTexture = 0;
	LPDIRECT3DVERTEXBUFFER9 psVertexBuffer = 0;
};
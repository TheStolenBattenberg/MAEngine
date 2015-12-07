#pragma once

/**
 * Note to self: Particle hard limit should be 32767 per system.
 */

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ParticleAttractor.h"
#include "ParticleRepulsor.h"

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();

	void createEmitter();
	void createAttractor();
	void createRepulsor();

	ParticleEmitter* getEmitter();

	void update(uint time);
	void render(); //Stub

	void setBlendMode(); //Stub
	void setTexture(LPDIRECT3DTEXTURE9 tex);

	uint getParticleCount();

	void setMaxParticleCount(uint max);
private:
	ParticleEmitter*   psEmitter = NULL;
	ParticleAttractor* psAttractor = NULL;
	ParticleRepulsor*  psRepulsor = NULL;

	std::vector<Particle> psBuffer;

	uint psMaxParticleCount;

	//D3D...
	LPDIRECT3DTEXTURE9 psTexture = 0;
	LPDIRECT3DVERTEXBUFFER9 psVertexBuffer = 0;
};
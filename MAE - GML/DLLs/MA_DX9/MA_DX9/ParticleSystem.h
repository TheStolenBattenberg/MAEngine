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
	void createEmitter();
	void createAttractor();
	void createRepulsor();

	void destroyAttractor(); //Stub
	void destroyEmitter(); //Stub
	void destroyRepulsor(); //Stub

	ParticleEmitter* getEmitter();

	void update(uint time);
	void render(); //Stub

	void setBlendMode(); //Stub

	uint getParticleCount();
private:
	ParticleEmitter*   psEmitter = NULL;
	ParticleAttractor* psAttractor = NULL;
	ParticleRepulsor*  psRepulsor = NULL;

	std::vector<Particle> psBuffer;

	//D3D...
	LPDIRECT3DTEXTURE9 psTexture; //Might be better to just have a 'MAE_SetTexture' call in GML for this.
	LPDIRECT3DVERTEXBUFFER9 psVertexBuffer;
	//No index buffer, since we're using point sprites.
};
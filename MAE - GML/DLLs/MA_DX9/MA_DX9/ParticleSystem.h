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

	void update(uint time);

private:
	ParticleEmitter*   psEmitter = NULL;
	ParticleAttractor* psAttractor = NULL;
	ParticleRepulsor*  psRepulsor = NULL;

	std::vector<Particle> psBuffer;
};
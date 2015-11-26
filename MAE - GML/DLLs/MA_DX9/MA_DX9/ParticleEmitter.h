#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"

class ParticleEmitter {
public:
	uint emitt(uint time, Particle*& parts);
	
private:
	vec4 pColourStart, pColourEnd;
	float pSizeMin, pSizeMax;

	uint pMinPerSecond, pMaxPerSecond;

	/**
	 * Note to self:
	 *	Use this to decide if the particle system should actually emitt. If Timer is equal to time, it should. Timer should then be set back to 0.
	 *  If it happens that timer isn't time, then it should return 0 so ParticleSystem skips the emitt stage.
	 *
	 */
	uint peTimer = 0;
};
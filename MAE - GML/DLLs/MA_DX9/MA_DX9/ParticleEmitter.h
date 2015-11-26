#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"

class ParticleEmitter {
public:
	enum EMITTER_TYPE {
		PE_BOX,
		PE_SPHERE,
		PE_CYLINDER
	};

	ParticleEmitter(EMITTER_TYPE type);

	uint emitt(uint time, Particle*& parts);
	
private:
	ColourRGBA pColourStart, pColourEnd;
	float pSizeMin, pSizeMax;

	uint pMinPerSecond, pMaxPerSecond;

	uint peTimer = 0;
};
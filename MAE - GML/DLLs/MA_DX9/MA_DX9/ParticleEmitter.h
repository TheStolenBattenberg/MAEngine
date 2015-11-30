#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"

enum EMITTER_TYPE {
	PE_BOX,
	PE_SPHERE,
	PE_CYLINDER
};

class ParticleEmitter {
public:
	ParticleEmitter(EMITTER_TYPE type);

	uint emitt(uint time, Particle*& parts);
	
	void setColour(ColourRGBA colourStart, ColourRGBA colourEnd);
	void setSize(float sizeMin, float sizeMax);
	void setSpawn(uint secondsMin, uint secondsMax);

private:
	ColourRGBA pColourStart, pColourEnd;
	float pSizeMin, pSizeMax;

	uint pMinPerSecond, pMaxPerSecond;

	uint peTimer = 0;
};
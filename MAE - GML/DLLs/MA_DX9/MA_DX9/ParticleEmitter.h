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

	uint emitt(uint time, uint count, Particle *parts);
	
	void setColour(ColourRGBA colourStart, ColourRGBA colourEnd);
	void setSize(float sizeMin, float sizeMax);
	void setSpawn(uint spawnMin, uint spawnMax);

	uint RandU(uint nMin, uint nMax);

	uint getSpawnThisTick();

private:
	ColourRGBA pColourStart, pColourEnd;
	float pSizeMin, pSizeMax;

	uint pMinPerEmitt, pMaxPerEmitt;

	uint peTimer = 0;
};
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
	
	void setColour(colourRGBAF colourStart, colourRGBAF colourEnd);
	void setSize(float sizeMin, float sizeMax);
	void setSpawn(uint spawnMin, uint spawnMax);
	void setLife(uint lifeMin, uint lifeMax);

	uint Rand(uint nMin, uint nMax);

	uint getSpawnThisTick();
	uint getMinEmitt();
	float getMinSize();
	float getMaxSize();

private:
	colourRGBAF pColourStart, pColourEnd;
	uint pMinLife, pMaxLife;
	float pMinSize, pMaxSize;

	uint pMinPerEmitt, pMaxPerEmitt;

	uint peTimer = 0;
};
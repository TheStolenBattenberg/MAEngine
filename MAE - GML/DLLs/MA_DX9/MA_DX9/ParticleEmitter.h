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
	
	void setPosition(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	void setVelocity(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	void setColour(float rMin, float gMin, float bMin, float aMin, float rMax, float gMax, float bMax, float aMax);
	void setLife(uint lifeMin, uint lifeMax);
	void setSize(float sizeMin, float sizeMax);

	void setAcceleration(float x, float y, float z);
	void setSpawn(uint spawnMin, uint spawnMax);

	float Rand(float nMin, float nMax);

	uint getSpawnThisTick();
	uint getMinEmitt();
	float getMinSize();
	float getMaxSize();
	vec3 getAcceleration();

private:
	vec3 pMinPosition, pMaxPosition;
	vec3 pMinVelocity, pMaxVelocity;
	colourRGBAF pColourStart, pColourEnd;
	uint pMinLife, pMaxLife;
	float pMinSize, pMaxSize;


	//Just for the emitter.
	vec3 pAcceleration;
	uint pMinPerEmitt, pMaxPerEmitt;
	uint peTimer = 0;
};
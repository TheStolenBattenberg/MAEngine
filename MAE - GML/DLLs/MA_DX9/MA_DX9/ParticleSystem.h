#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"


class ParticleSystem {
public:
	~ParticleSystem();
	ParticleSystem(uint particlecount);

	//Relocate this.
	float randomRange(float floor, float ceiling);

	//Could be a void, but I want it to return an index incase we want to modify particles directly,
	//rather than letting the system handle it.
	uint addParticle(uint index);
	void removeParticle(uint index);

	void updateSystem();
	void renderSystem();


	//Functions that set default variables when spawning particles.
	void setSystemAdditiveBlending(bool truefalse);
	void setSystemPosition(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
	void setSystemVelocity(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
	void setSystemColour(float rMin, float gMin, float bMin, float aMin, float rMax, float gMax, float bMax, float aMax);
	void setSystemLife(float lifeMin, float lifeMax);
	void setSystemSize(float sizeMin, float sizeMax);

private:
	/**
	 * TO-DO: Make default values for these.
	 */
	bool pUseAdditiveBlending;
	vec3 psPositionMin;
	vec3 psPositionMax;
	vec3 psVelocityMin;
	vec3 psVelocityMax;
	vec4 psColourMin;
	vec4 psColourMax;

	float psLifeMin;
	float psLifeMax;
	float psSizeMin;
	float psSizeMax;

	uint psParticleCount;
	std::vector<Particle> pBuffer;

	//D3D
};
#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"

class ParticleAttractor {
public:
	void setDistance(float dist);
	void setGravity(float grav);
	void setPosition(vec3 pos);

	float getDistance();
	float getGravity();
	vec3  getPosition();
private:
	float paDistance;
	float paGravity;
	vec3  paPosition;
};
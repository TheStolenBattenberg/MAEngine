#pragma once

/**
* Includes
*/
#include "Types.h"
#include "Particle.h"

class ParticleRepulsor {
public:
	void setDistance(float dist);
	void setGravity(float grav);
	void setPosition(vec3 pos);

	float getDistance();
	float getGravity();
	vec3  getPosition();
private:
	float prDistance;
	float prGravity;
	vec3  prPosition;
};
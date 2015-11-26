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
	void setPosition(Vector3D pos);

	float getDistance();
	float getGravity();
	Vector3D  getPosition();
private:
	float paDistance;
	float paGravity;
	Vector3D paPosition;
};
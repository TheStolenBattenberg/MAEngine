#pragma once

/**
* Includes
*/
#include "Types.h"

struct Particle {
	vec3 pPosition; //Position of the particle
	vec3 pVelocity; //Velocity
	vec4 pColour; //Colour of the particle.
	uint pAge; //The current age of the particle.
	uint pLife; //The age at which the particle dies.
	float pSize;
};

struct ParticlePoint {
	vec3 pPosition;
	vec4 pColour;
	float pSize;
};
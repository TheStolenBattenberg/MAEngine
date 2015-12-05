#pragma once

/**
* Includes
*/
#include "Types.h"

struct Particle {
	vec3 pPosition; //Position of the particle
	vec3 pDirection; //Direction of the particle. X, Y & Z should be between -1 and +1.
	colourRGBAF pColour; //Colour of the particle.
	float pAcceleration; //The speed of the particle
	float pSize; //The size of the particle.
	uint pAge; //The current age of the particle.
	uint pLife; //The age at which the particle dies.
};
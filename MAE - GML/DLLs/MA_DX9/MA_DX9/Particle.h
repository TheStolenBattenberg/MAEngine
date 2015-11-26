#pragma once

/**
* Includes
*/

#include "Types.h"

struct Particle {
	Vector3D pPosition; //Position of the particle
	Vector3D pDirection; //Direction of the particle. X, Y & Z should be between -1 and +1.
	ColourRGBA pColour; //Colour of the particle.
	float pAcceleration; //The speed of the particle
	float pSize; //The size of the particle.
	uint pAge; //The current age of the particle.
	uint pLife; //The age at which the particle dies.
};
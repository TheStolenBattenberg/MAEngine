#pragma once

/**
* Includes
*/
#include <MAE/Core/Types.h>
#include <MAE/Core/Vec.h>

struct Particle {
	vec3 vPosition; //Position of the particle
	vec3 vVelocity; //Velocity
	vec4 vColour; //Colour of the particle.
	uint iAge; //The current age of the particle.
	uint iLife; //The age at which the particle dies.
	float fSize;
};

struct ParticlePoint {
	vec3 vPosition;
	vec4 vColour;
	float fSize;
};
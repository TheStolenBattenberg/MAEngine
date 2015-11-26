#pragma once

/**
* Includes
*/

#include "Types.h"

struct Particle {
	vec3 pPosition; //The position of the particle.
	vec3 pVelocity; //The velocity of the particle.
	vec4 pDiffuse;  //The colour of the particle.
	float pAge;     //The age of the particle since creation.
	float pLife;    //The life of the partice. if age is greater than life, destroy the particle.
	float pSize;    //The size of the particle.
};
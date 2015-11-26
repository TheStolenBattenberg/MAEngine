#include "Main.h"

ParticleEmitter::ParticleEmitter(EMITTER_TYPE type) {
	switch (type) {
		case PE_BOX: {

		}
		break;

		case PE_SPHERE: {
			/**
			 * No idea how to do this shape.
			 */
		}
		break;

		case PE_CYLINDER: {

		}
		break;
	}
}

/**
 * TO-DO: make it actually emitt particles.
 */
uint ParticleEmitter::emitt(uint time, Particle*& parts) {
	if (peTimer == time) {

		peTimer = 0;
	}
	
	//If peTimer isn't equal to time, it'll increment it, and return 0 so the Particle System doesn't try to add particles.
	peTimer++;
	return 0;
}
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
uint ParticleEmitter::emitt(uint time, uint count, Particle *parts) {
	if (peTimer == time) {
		//Emitt particles inside this if statement.
		Particle part;
		for (uint i = 0; i < count; i++) {
			part.pLife = RandU(30, 90);
			part.pAge = 0;

			//TEMP
			part.pAcceleration = 0;
			part.pColour.r = 0;
			part.pColour.g = 0;
			part.pColour.b = 0;
			part.pColour.a = 0;
			part.pDirection.x = 0;
			part.pDirection.y = 0;
			part.pDirection.z = 0;
			part.pPosition.x = 0;
			part.pPosition.y = 0;
			part.pPosition.z = 0;
			part.pSize = 0;

			parts[i] = part;
		}
		peTimer = 0;
		return count;
	}
	peTimer++;
	return 0;
}

void ParticleEmitter::setSpawn(uint spawnMin, uint spawnMax) {
	pMinPerEmitt = spawnMin;
	pMaxPerEmitt = spawnMax;
}

uint ParticleEmitter::getSpawnThisTick() {
	return pMaxPerEmitt + (int)((double)rand() / (RAND_MAX + 1) * (pMaxPerEmitt - pMinPerEmitt + 1));
}

uint ParticleEmitter::RandU(uint min, uint max) {
	return min + (uint)((double)rand() / (RAND_MAX + 1) * (max - min + 1));
}
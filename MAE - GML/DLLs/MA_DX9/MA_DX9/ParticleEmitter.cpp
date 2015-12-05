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
			part.pLife = Rand(pMinLife, pMaxLife);
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

void ParticleEmitter::setSize(float sizeMin, float sizeMax) {
	pMinSize = sizeMin;
	pMaxSize = sizeMax;
}

void ParticleEmitter::setLife(uint lifeMin, uint lifeMax) {
	pMinLife = lifeMin;
	pMaxLife = lifeMax;
}

uint ParticleEmitter::getSpawnThisTick() {
	return Rand(pMinPerEmitt, pMaxPerEmitt);
}

uint ParticleEmitter::Rand(uint min, uint max) {
	//return min + (uint) ((double) rand() / ((RAND_MAX + 1) * (max - min + 1)));
	return rand() % ((max - min) + (min+1));
}

uint ParticleEmitter::getMinEmitt() {
	return pMinPerEmitt;
}

float ParticleEmitter::getMinSize() {
	return pMinSize;
}

float ParticleEmitter::getMaxSize() {
	return pMaxSize;
}
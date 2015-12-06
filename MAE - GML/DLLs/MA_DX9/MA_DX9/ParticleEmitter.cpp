#include "Main.h"
#include "ParticleEmitter.h"

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
		Particle part;

		for (uint i = 0; i < count; i++) {
			part.pPosition.x = Rand(pMinPosition.x, pMaxPosition.x); //Set Position.
			part.pPosition.y = Rand(pMinPosition.y, pMaxPosition.y);
			part.pPosition.z = Rand(pMinPosition.z, pMaxPosition.z);

			part.pVelocity.x = Rand(pMinVelocity.x, pMaxVelocity.x); //Set Velocity.
			part.pVelocity.x = Rand(pMinVelocity.y, pMaxVelocity.y);
			part.pVelocity.x = Rand(pMinVelocity.z, pMaxVelocity.z);

			part.pColour.r   = 255; //Set Colour
			part.pColour.g   = 255;
			part.pColour.b   = 255;
			part.pColour.a   = 255;

			part.pAge        = 0; //Set Age.

			part.pLife       = (uint)Rand((float) pMinLife, (float)pMaxLife); //Set Life

			part.pSize       = Rand(pMinSize, pMaxSize);

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

void ParticleEmitter::setPosition(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	pMinPosition.x = minX;
	pMinPosition.y = minY;
	pMinPosition.z = minZ;
	pMaxPosition.x = maxX;
	pMaxPosition.y = maxY;
	pMaxPosition.z = maxZ;
}

void ParticleEmitter::setVelocity(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	pMinVelocity.x = minX;
	pMinVelocity.y = minY;
	pMinVelocity.z = minZ;
	pMaxVelocity.x = maxX;
	pMaxVelocity.y = maxY;
	pMaxVelocity.z = maxZ;
}

void ParticleEmitter::setAcceleration(float x, float y, float z) {
	pAcceleration.x = x;
	pAcceleration.y = y;
	pAcceleration.z = z;
}

uint ParticleEmitter::getSpawnThisTick() {
	return (uint)Rand((float)pMinPerEmitt, (float)pMaxPerEmitt);
}

float ParticleEmitter::Rand(float min, float max) {
	return (float)rand() / RAND_MAX * (max - min) + min;
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

vec3 ParticleEmitter::getAcceleration() {
	return pAcceleration;
}
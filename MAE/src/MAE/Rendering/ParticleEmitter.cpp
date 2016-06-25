#include <MAE/Main.h>
#include <MAE/Rendering/ParticleEmitter.h>
#include <MAE/Core/Math.h>

ParticleEmitter::ParticleEmitter(EMITTER_TYPE type) {
	switch (type) {
		case PE_BOX: {

		}
		break;

		case PE_SPHERE: {

		}
		break;

		case PE_CYLINDER: {

		}
		break;
	}
}

uint ParticleEmitter::emitt(uint time, uint count, Particle *parts) {
	if (peTimer == time) {
		Particle part;

		for (uint i = 0; i < count; i++) {
			part.pPosition.x = interpLinear(pMinPosition.x, pMaxPosition.x, (float) rand() / RAND_MAX); //Set Position.
			part.pPosition.y = interpLinear(pMinPosition.y, pMaxPosition.y, (float) rand() / RAND_MAX);
			part.pPosition.z = interpLinear(pMinPosition.z, pMaxPosition.z, (float) rand() / RAND_MAX);

			part.pVelocity.x = interpLinear(pMinVelocity.x, pMaxVelocity.x, (float) rand() / RAND_MAX); //Set Velocity.
			part.pVelocity.y = interpLinear(pMinVelocity.y, pMaxVelocity.y, (float) rand() / RAND_MAX);
			part.pVelocity.z = interpLinear(pMinVelocity.z, pMaxVelocity.z, (float) rand() / RAND_MAX);

			part.pColour.x   = pColourStart.x;
			part.pColour.y   = pColourStart.y;
			part.pColour.z   = pColourStart.z;
			part.pColour.w   = pColourStart.w;

			part.pAge        = 0;

			part.pLife       = interpLinear(pMinLife, pMaxLife, (float) rand() / RAND_MAX);

			part.pSize       = interpLinear(pMinSize, pMaxSize, (float) rand() / RAND_MAX);

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

void ParticleEmitter::setColour(float rMin, float gMin, float bMin, float aMin, float rMax, float gMax, float bMax, float aMax) {
	pColourStart.x = rMin;
	pColourStart.y = gMin;
	pColourStart.z = bMin;
	pColourStart.w = aMin;
	pColourEnd.x   = rMax;
	pColourEnd.y   = gMax;
	pColourEnd.z   = bMax;
	pColourEnd.w   = aMax;

	if (rMin != rMax || gMin != gMax || bMin != bMax || aMin != aMax){
		interpColours = true;
	}
	else {
		interpColours = false;
	}
}

void ParticleEmitter::setAcceleration(float x, float y, float z) {
	pAcceleration.x = x;
	pAcceleration.y = y;
	pAcceleration.z = z;
}

uint ParticleEmitter::getSpawnThisTick() {
	return interpLinear(pMinPerEmitt, pMaxPerEmitt, (float) rand() / RAND_MAX);
}

vec4 ParticleEmitter::getColour(float interp) {	
	if (interpColours) {
		vec4 col = pColourStart;
		float m = (1.0f / interp);
		col.x = interpCosine(pColourStart.x, pColourEnd.x, 1.0f - m);
		col.y = interpCosine(pColourStart.y, pColourEnd.y, 1.0f - m);
		col.z = interpCosine(pColourStart.z, pColourEnd.z, 1.0f - m);
		col.w = interpCosine(pColourStart.w, pColourEnd.w, 1.0f - m);
		return col;
	}else {
		return pColourStart;
	}
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
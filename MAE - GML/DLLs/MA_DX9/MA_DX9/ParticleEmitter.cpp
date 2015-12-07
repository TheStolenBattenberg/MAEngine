#include "Main.h"
#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(EMITTER_TYPE type) {
	//This does nothing. Surprise!
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
			part.pPosition.x = Rand(pMinPosition.x, pMaxPosition.x); //Set Position.
			part.pPosition.y = Rand(pMinPosition.y, pMaxPosition.y);
			part.pPosition.z = Rand(pMinPosition.z, pMaxPosition.z);

			part.pVelocity.x = Rand(pMinVelocity.x, pMaxVelocity.x); //Set Velocity.
			part.pVelocity.y = Rand(pMinVelocity.y, pMaxVelocity.y);
			part.pVelocity.z = Rand(pMinVelocity.z, pMaxVelocity.z);

			part.pColour.x   = pColourStart.x; //Colour
			part.pColour.y   = pColourStart.y; //Colour
			part.pColour.z   = pColourStart.z; //Colour
			part.pColour.w   = pColourStart.w; //Colour

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

void ParticleEmitter::setColour(float rMin, float gMin, float bMin, float aMin, float rMax, float gMax, float bMax, float aMax) {
	pColourStart.x = rMin;
	pColourStart.y = gMin;
	pColourStart.z = bMin;
	pColourStart.w = aMin;
	pColourEnd.x   = rMax;
	pColourEnd.y   = gMax;
	pColourEnd.z   = bMax;
	pColourEnd.w   = aMax;
}

void ParticleEmitter::setAcceleration(float x, float y, float z) {
	pAcceleration.x = x;
	pAcceleration.y = y;
	pAcceleration.z = z;
}

uint ParticleEmitter::getSpawnThisTick() {
	return (uint)Rand((float)pMinPerEmitt, (float)pMaxPerEmitt);
}

//Gotta move this to a math class.
float ParticleEmitter::Rand(float min, float max) {     //Random Range
	return (float)rand() / RAND_MAX * (max - min) + min;
}

//Same as above.
float ParticleEmitter::Cerp(float x, float y, float s) { //Cosine Interpolation
	float interp = (float)(1 - cos(s*3.14)) / 2;
	return(x*(1 - interp) + y*interp);
}

//This probably should not automatically interpolate the colours
vec4 ParticleEmitter::getColour(float interp) {
	vec4 col = pColourStart;
	if (interp > 2.0f) { //HACKY AS F***... Replace this ASAP.
		float m = (1.0f / (interp));
		col.x = Cerp(pColourStart.x, pColourEnd.x, 1.0f - m);
		col.y = Cerp(pColourStart.y, pColourEnd.y, 1.0f - m);
		col.z = Cerp(pColourStart.z, pColourEnd.z, 1.0f - m);
		col.w = Cerp(pColourStart.w, pColourEnd.w, 1.0f - m);
	}
	return col;
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
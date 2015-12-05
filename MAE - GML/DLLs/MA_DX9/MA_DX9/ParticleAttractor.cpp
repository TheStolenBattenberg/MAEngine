#include "Main.h"
#include "ParticleAttractor.h"

void ParticleAttractor::setDistance(float dist) {
	paDistance = dist;
}

void ParticleAttractor::setGravity(float grav) {
	paGravity = grav;
}

void ParticleAttractor::setPosition(vec3 pos) {
	paPosition = pos;
}

float ParticleAttractor::getDistance() {
	return paDistance;
}

float ParticleAttractor::getGravity() {
	return paGravity;
}

vec3 ParticleAttractor::getPosition() {
	return paPosition;
}

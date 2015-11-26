#include "Main.h"

void ParticleAttractor::setDistance(float dist) {
	paDistance = dist;
}

void ParticleAttractor::setGravity(float grav) {
	paGravity = grav;
}

void ParticleAttractor::setPosition(Vector3D pos) {
	paPosition = pos;
}

float ParticleAttractor::getDistance() {
	return paDistance;
}

float ParticleAttractor::getGravity() {
	return paGravity;
}

Vector3D ParticleAttractor::getPosition() {
	return paPosition;
}
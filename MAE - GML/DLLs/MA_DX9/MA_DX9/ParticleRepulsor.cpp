#include "Main.h"
#include "ParticleRepulsor.h"

void ParticleRepulsor::setDistance(float dist) {
	prDistance = dist;
}

void ParticleRepulsor::setGravity(float grav) {
	prGravity = grav;
}

void ParticleRepulsor::setPosition(vec3 pos) {
	prPosition = pos;
}

float ParticleRepulsor::getDistance() {
	return prDistance;
}

float ParticleRepulsor::getGravity() {
	return prGravity;
}

vec3 ParticleRepulsor::getPosition() {
	return prPosition;
}

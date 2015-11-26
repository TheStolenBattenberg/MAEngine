#include "Main.h"

void ParticleRepulsor::setDistance(float dist) {
	prDistance = dist;
}

void ParticleRepulsor::setGravity(float grav) {
	prGravity = grav;
}

void ParticleRepulsor::setPosition(Vector3D pos) {
	prPosition = pos;
}

float ParticleRepulsor::getDistance() {
	return prDistance;
}

float ParticleRepulsor::getGravity() {
	return prGravity;
}

Vector3D ParticleRepulsor::getPosition() {
	return prPosition;
}
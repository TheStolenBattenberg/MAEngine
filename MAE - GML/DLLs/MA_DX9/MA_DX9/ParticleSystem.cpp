#include "Main.h"
#include <iostream>

void ParticleSystem::createEmitter() {
	/**
	 * This needs to be changed. We should have multiple emitter shapes, like sphere, box, cylinder etc.
	 */
	psEmitter = new ParticleEmitter(PE_BOX);
}

void ParticleSystem::createAttractor() {
	psAttractor = new ParticleAttractor();
}

void ParticleSystem::createRepulsor() {
	psRepulsor = new ParticleRepulsor();
}

ParticleEmitter* ParticleSystem::getEmitter() {
	return psEmitter;
}

void ParticleSystem::update(uint time) {
	if (psEmitter != NULL) {

		uint pC = psEmitter->getSpawnThisTick();

		Particle* parts = new Particle[pC];

		uint partCount = psEmitter->emitt(time, pC, parts);

		if (partCount > 0) {
			for (uint i = 0; i < partCount; ++i) {
				psBuffer.push_back(parts[i]);
			}
		}
		delete[] parts;
	}

	uint i = 0;
	while (i < psBuffer.size()) {
		if (psBuffer[i].pAge > psBuffer[i].pLife)
		{
			psBuffer[i] = psBuffer[psBuffer.size() - 1];
			psBuffer.pop_back();
		}
		else {
			if (psAttractor != NULL) {
				//Move the particles towards if in range.
			}

			if (psRepulsor != NULL) {
				//Move the particles away if in range.
			}

			//Normal movement, via velocity.

			//Velocity increase math: POS.X + VEL.X * ACCELERATION.

			//Also do the other particle effects here, such as interp between colours, based on life. Probably a lot more too
			psBuffer[i].pAge++;
			++i;
		}
	}
}

uint ParticleSystem::getParticleCount() {
	return psBuffer.size();
}
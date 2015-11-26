#include "Main.h"

void ParticleSystem::createEmitter() {
	/**
	 * This needs to be changed. We should have multiple emitter shapes, like sphere, box, cylinder etc.
	 */
	psEmitter = new ParticleEmitter();
}

void ParticleSystem::createAttractor() {
	psAttractor = new ParticleAttractor();
}

void ParticleSystem::createRepulsor() {
	psRepulsor = new ParticleRepulsor();
}

void ParticleSystem::update(uint time) {
	if (psEmitter != NULL) {
		Particle* parts;
		uint partCount = psEmitter->emitt(time, parts);

		if (partCount > 0) {
			uint pCountNow = 32767 - psBuffer.size();

			if (partCount > pCountNow)
				partCount = pCountNow;

			for (uint i = psBuffer.size(); i < pCountNow + partCount; ++i) {
				psBuffer[i] = parts[i - partCount];
			}
		}
	}

	uint i = 0;
	while (i < psBuffer.size()) {
		if (psBuffer[i].pAge > psBuffer[i].pLife)
		{
			psBuffer[i] = psBuffer[psBuffer.size() - 1];
			//psBuffer.erase(psBuffer.size() - 1); erase doesn't like particles? Not sure what to do here, I'm guessing it's simple, I'm just
			//not too experienced with C++.
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
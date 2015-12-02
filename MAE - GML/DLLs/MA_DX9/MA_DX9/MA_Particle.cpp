#include "Main.h"
#include "Types.h"

/**
 * Temporary API, just for debugging. Will need to add particle system index's and such.
 */

DLLEXPORT double MADX9_ParticleSystemCreate() {
	mamain->ParticleSys = new ParticleSystem();
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemUpdate(double step) {
	mamain->ParticleSys->update((uint) step);
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemGetParticleCount() {
	return mamain->ParticleSys->getParticleCount();
}

DLLEXPORT double MADX9_ParticleEmitterCreate() {
	mamain->ParticleSys->createEmitter();
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleCount(double min, double max) {
	mamain->ParticleSys->getEmitter()->setSpawn((uint) min, (uint) max);
	return 1;
}
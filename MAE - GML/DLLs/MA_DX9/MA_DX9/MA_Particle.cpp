#include "Main.h"
#include "Types.h"
#include "ParticleSystem.h"
#include "Resources.h"

/**
 * Temporary API, just for debugging. Will need to add particle system index's and such.
 * Will need to add error checking and such.
 */

DLLEXPORT double MADX9_ParticleSystemCreate() {
	mamain->ParticleSys = new ParticleSystem();
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemUpdate(double step) {
	mamain->ParticleSys->update((uint) step);
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemRender() {
	mamain->ParticleSys->render();
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemGetParticleCount() {
	return mamain->ParticleSys->getParticleCount();
}

DLLEXPORT double MADX9_ParticleSystemSetParticleCount(double count) {
	mamain->ParticleSys->setMaxParticleCount((uint)count);
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemSetTexture(double texInd) {
	if ((uint)texInd >= mamain->Textures.size())
		return 0;

	if (mamain->Textures[(uint)texInd] == 0)
		return 0;

	mamain->ParticleSys->setTexture(mamain->Textures[(uint)texInd]->tex);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterCreate() {
	mamain->ParticleSys->createEmitter();
	mamain->ParticleSys->getEmitter()->setAcceleration((float)-0.005, (float)0, (float)0);
	mamain->ParticleSys->getEmitter()->setVelocity(-1, 0, 0, -1, 0, 0);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleSize(double min, double max) {
	mamain->ParticleSys->getEmitter()->setSize((float) min, (float) max);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleCount(double min, double max) {
	mamain->ParticleSys->getEmitter()->setSpawn((uint) min, (uint) max);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleLife(double min, double max) {
	mamain->ParticleSys->getEmitter()->setLife((uint) min, (uint) max);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticlePos(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	mamain->ParticleSys->getEmitter()->setPosition((float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ);
	return 1;
}
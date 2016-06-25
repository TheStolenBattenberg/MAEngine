#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <GMLAPI/Main.h>
#include <MAE/Rendering/ParticleSystem.h>

/**
 * Temporary API, just for debugging. Will need to add particle system index's and such.
 * Will need to add error checking and such.
 */

DLLEXPORT double MADX9_ParticleSystemCreate() 
{
	ParticleSystem* ps = new ParticleSystem();
	return putInto(ps, mamain->ParticleSys);
}

DLLEXPORT double MADX9_ParticleSystemDestroy(double index) 
{
	if (!isValidIndex((uint)index, mamain->ParticleSys))
		return 0;

	delete mamain->ParticleSys[(uint)index];
	mamain->ParticleSys[(uint)index] = 0;

	return 1;
}

DLLEXPORT double MADX9_ParticleSystemUpdate(double index, double step) {
	mamain->ParticleSys[(uint)index]->update((uint) step);
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemRender(double index) {
	mamain->ParticleSys[(uint)index]->render();
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemGetParticleCount(double index) {
	return mamain->ParticleSys[(uint)index]->getParticleCount();
}

DLLEXPORT double MADX9_ParticleSystemSetParticleCount(double index, double count) {
	mamain->ParticleSys[(uint)index]->setMaxParticleCount((uint)count);
	return 1;
}

DLLEXPORT double MADX9_ParticleSystemSetTexture(double index, double texInd) {
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	mamain->ParticleSys[(uint) index]->setTexture(tex);

	return ErrorOk;
}

DLLEXPORT double MADX9_ParticleEmitterCreate(double index) {
	mamain->ParticleSys[(uint)index]->createEmitter();
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticlePos(double index, double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setPosition((float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleVel(double index, double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setVelocity((float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleCol(double index, double startR, double startG, double startB, double startA, double endR, double endG, double endB, double endA) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setColour((float) startR, (float) startG, (float) startB, (float) startA, (float) endR, (float) endG, (float) endB, (float) endA);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleAcc(double index, double x, double y, double z) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setAcceleration((float)x, (float)y, (float)z);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleSize(double index, double min, double max) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setSize((float) min, (float) max);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleCount(double index, double min, double max) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setSpawn((uint) min, (uint) max);
	return 1;
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleLife(double index, double min, double max) {
	mamain->ParticleSys[(uint)index]->getEmitter()->setLife((uint) min, (uint) max);
	return 1;
}
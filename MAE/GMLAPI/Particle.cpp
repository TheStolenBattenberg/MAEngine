#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>
#include <MAE/Rendering/ParticleSystem.h>

/**
 * Temporary API, just for debugging. Will need to add particle system index's and such.
 * Will need to add error checking and such.
 */

DLLEXPORT double MADX9_ParticleSystemCreate() {
	TRYBEG();
	auto ps = new ParticleSystem(renderer);

	mamain->ParticleSys.add(ps);
	return ptrToDouble(ps);
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleSystemDestroy(double ps) {
	TRYBEG();
	auto ptr = doubleToPtr<ParticleSystem>(ps);

	mamain->ParticleSys.remove(ptr);
	delete ptr;

	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleSystemUpdate(double ps, double step) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->update((uint) step);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleSystemRender(double ps) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->render();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleSystemGetParticleCount(double ps) {
	TRYBEG();
	return doubleToPtr<ParticleSystem>(ps)->getParticleCount();
	TRYEND(-1);
}

DLLEXPORT double MADX9_ParticleSystemSetParticleCount(double ps, double count) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->setMaxParticleCount((uint)count);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleSystemSetTexture(double ps, double tex) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->setTexture(doubleToPtr<Texture>(tex));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterCreate(double ps) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->createEmitter();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticlePos(double ps, double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setPosition((float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleVel(double ps, double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setVelocity((float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleCol(double ps, double startR, double startG, double startB, double startA, double endR, double endG, double endB, double endA) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setColour((float) startR, (float) startG, (float) startB, (float) startA, (float) endR, (float) endG, (float) endB, (float) endA);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleAcc(double ps, double x, double y, double z) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setAcceleration((float)x, (float)y, (float)z);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleSize(double ps, double min, double max) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setSize((float) min, (float) max);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleCount(double ps, double min, double max) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setSpawn((uint) min, (uint) max);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_ParticleEmitterSetParticleLife(double ps, double min, double max) {
	TRYBEG();
	doubleToPtr<ParticleSystem>(ps)->getEmitter()->setLife((uint) min, (uint) max);
	return 1;
	TRYEND(0);
}
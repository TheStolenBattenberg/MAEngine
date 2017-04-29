#include <MAE/Main.h>
#include <MAE/Rendering/ParticleEmitter.h>

uint ParticleEmitter::EmitterBox(uint time, uint count, Particle* particles) {
	if (iTimer == time) {
		Particle Part;

		for (uint i = 0; i < count; ++i) {
			Part.vPosition.x = interpLinear(vMinPosition.x, vMaxPosition.x, (float)rand() / RAND_MAX);
			Part.vPosition.y = interpLinear(vMinPosition.y, vMaxPosition.y, (float)rand() / RAND_MAX);
			Part.vPosition.z = interpLinear(vMinPosition.z, vMaxPosition.z, (float)rand() / RAND_MAX);

			Part.vVelocity.x = interpLinear(vMinVelocity.x, vMaxVelocity.x, (float)rand() / RAND_MAX);
			Part.vVelocity.y = interpLinear(vMinVelocity.y, vMaxVelocity.y, (float)rand() / RAND_MAX);
			Part.vVelocity.z = interpLinear(vMinVelocity.z, vMaxVelocity.z, (float)rand() / RAND_MAX);
			Part.vColour = vColour;
			Part.iAge = 0;
			Part.iLife = interpLinear(iMinLife, iMaxLife, (float)rand() / RAND_MAX);
			Part.fSize = interpLinear(fMinSize, fMaxSize, (float)rand() / RAND_MAX);

			particles[i] = Part;
		}
		iTimer = 0;
		return count;
	}
	++iTimer;

	return 0;
}

//
// Emitter Types.
//
uint ParticleEmitter::Emitt(uint time, uint count, Particle* parts) {
	switch (eType) {
	case PETYPE::PECUBE:
		return EmitterBox(time, count, parts);
		break;
	}
	return 0;
}

//
// Setters.
//
void ParticleEmitter::SetMinPosition(float x, float y, float z) {
	vMinPosition.x = x;
	vMinPosition.y = y;
	vMinPosition.z = z;
}
void ParticleEmitter::SetMaxPosition(float x, float y, float z) {
	vMaxPosition.x = x;
	vMaxPosition.y = y;
	vMaxPosition.z = z;
}

void ParticleEmitter::SetMinVelocity(float x, float y, float z) {
	vMinVelocity.x = x;
	vMinVelocity.y = y;
	vMinVelocity.z = z;
}
void ParticleEmitter::SetMaxVelocity(float x, float y, float z) {
	vMaxVelocity.x = x;
	vMaxVelocity.y = y;
	vMaxVelocity.z = z;
}

void ParticleEmitter::SetColour(float r, float g, float b, float a) {
	vColour.x = r;
	vColour.y = g;
	vColour.z = b;
	vColour.w = a;
}

void ParticleEmitter::SetMinLife(uint life) {
	iMinLife = life;
}
void ParticleEmitter::SetMaxLife(uint life) {
	iMaxLife = life;
}

void ParticleEmitter::SetMinSize(float size) {
	fMinSize = size;
}
void ParticleEmitter::SetMaxSize(float size) {
	fMaxSize = size;
}

void ParticleEmitter::SetAcceleration(float x, float y, float z) {
	vAcceleration.x = x;
	vAcceleration.y = y;
	vAcceleration.z = z;
}

void ParticleEmitter::SetMinEmitt(uint emitt) {
	iMinEmitt = emitt;
}
void ParticleEmitter::SetMaxEmitt(uint emitt) {
	iMaxEmitt = emitt;
}

void ParticleEmitter::SetTimer(uint time) {
	iTimer = time;
}

vec3 ParticleEmitter::GetAcceleration() {
	return vAcceleration;
}

uint ParticleEmitter::GetMinLife() {
	return iMinLife;
}
uint ParticleEmitter::GetMaxLife() {
	return iMaxLife;
}

float ParticleEmitter::GetMinSize() {
	return fMinSize;
}
float ParticleEmitter::GetMaxSize() {
	return fMaxSize;
}
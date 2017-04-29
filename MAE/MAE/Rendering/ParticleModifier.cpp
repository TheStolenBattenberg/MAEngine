#include <MAE/Main.h>
#include <MAE/Rendering/ParticleModifier.h>

ParticleModifier::ParticleModifier(PMTYPE type) {
	pmType = type;
}

Particle ParticleModifier::Apply(Particle part) {
	switch (pmType) {
	case PMTYPE::PMGRAVITY:
		part.vPosition.x = part.vPosition.x + (fForce * vDir.x);
		part.vPosition.y = part.vPosition.y + (fForce * vDir.y);
		part.vPosition.z = part.vPosition.z + (fForce * vDir.z);
		break;

	case PMTYPE::PMWIGGLE:
		part.vPosition.x = part.vPosition.x + (float)((cos(fTime)*cos(fTime)) * (fForce * vDir.x));
		part.vPosition.y = part.vPosition.y + (float)((sin(fTime)*cos(fTime)) * (fForce * vDir.y));
		part.vPosition.z = part.vPosition.z + (float)(cos(fTime) * (fForce * vDir.z));
		break;

	case PMTYPE::PMSPREAD:
		part.vPosition.x = part.vPosition.x * fForce;
		part.vPosition.y = part.vPosition.y * fForce;
		part.vPosition.z = part.vPosition.z * fForce;
		break;
	}
	return part;
}

void ParticleModifier::setDir(float x, float y, float z) {
	vDir.x = x;
	vDir.y = y;
	vDir.z = z;
}

void ParticleModifier::setForce(float force) {
	fForce = force;
}

void ParticleModifier::setTime(double time) {
	fTime = time;
}

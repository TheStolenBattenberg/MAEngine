#include "Main.h"
#include "ParticleModifier.h"

void ParticleModifier::update(Particle *part) {
	if (life = 0 && undying == false) {
		//Destroy.
	}
	
	switch (pm_Type) {
		case PMEffect::PE_GRAVITY:
			part->pPosition.x -= 0; //obviously this isn't going to do anything.
			part->pPosition.y -= 0;
			part->pPosition.z -= 0;
		break;
	}
	//Do things.
	
	life--;
}

void ParticleModifier::setType(PMEffect type) {
	pm_Type = type;
}

void ParticleModifier::setLife(uint lf) {
	if (life == 0) {
		undying = true;
	}
	life = lf;
}

void ParticleModifier::setParamFloat(PMEffectParam PEP, float val) {
	//to do
}

void ParticleModifier::setPosition(float x, float y, float z) {
	//to do
}
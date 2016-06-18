#pragma once

/**
 * Includes
 */
#include <MAE/Core/Types.h>
#include <MAE/Rendering/Particle.h>

class ParticleModifier {
public:
	enum PMEffect {
		PE_GRAVITY,
		PE_WIGGLE,
		PE_ENLARGE
	};

	enum PMEffectParam {
		PEP_GRAVITY,		//Base value to pull/push particles by.
		PEP_WIGGLE,			//How intense a particle should 'wiggle'.
		PEP_ENLARGE			//How much a particle should increase/decrease in size.
	};

	void setPosition(float x, float y, float z);
	void setParamFloat(PMEffectParam PEP, float val); //Remake this with templates, so 'val' can be different types, i.e vec3.
	void setType(PMEffect type);

	void setLife(uint lf);
	void update(Particle *part);
private:
	uint life;
	bool undying;

	PMEffect pm_Type;
};
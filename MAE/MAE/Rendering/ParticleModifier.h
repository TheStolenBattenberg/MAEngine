#pragma once

/**
 * Includes
 */
#include <MAE/Rendering/Particle.h>
#include <MAE/Core/Math.h>

enum PMTYPE {
	PMGRAVITY = 0,
	PMWIGGLE  = 1,
	PMSPREAD  = 2,
};

class ParticleModifier {
public:
	ParticleModifier(PMTYPE type);

	Particle Apply(Particle part);

	void setDir(float x, float y, float z);
	void setForce(float force);
	void setTime(double time);

private:
	PMTYPE pmType;

	vec3 vDir;
	float fForce;
	double fTime;
};
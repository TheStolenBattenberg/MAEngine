#pragma once

/**
* Includes
*/
#include <MAE/Rendering/Particle.h>
#include <MAE/Core/Math.h>

enum PETYPE {
	PECUBE,
	PESPHERE,
};

class ParticleEmitter {
public:
	//
	// Functions
	//
	uint Emitt(uint time, uint count, Particle* particles);
	uint EmitterBox(uint time, uint count, Particle* particles);

	//
	// Setters
	//
	void SetMinPosition(float x, float y, float z);
	void SetMaxPosition(float x, float y, float z);
	void SetMinVelocity(float x, float y, float z);
	void SetMaxVelocity(float x, float y, float z);
	void SetColour(float r, float g, float b, float a);
	void SetMinLife(uint life);
	void SetMaxLife(uint life);
	void SetMinSize(float size);
	void SetMaxSize(float size);
	void SetAcceleration(float x, float y, float z);
	void SetMinEmitt(uint emitt);
	void SetMaxEmitt(uint emitt);
	void SetTimer(uint time);

	//
	// Getters.
	//
	vec3   GetAcceleration();
	uint   GetMinLife();
	uint   GetMaxLife();
	float  GetMinSize();
	float  GetMaxSize();
	uint   GetMinEmitt();
	uint   GetMaxEmitt();
	uint   GetTimer();

private:
	vec3 vMinPosition, vMaxPosition;
	vec3 vMinVelocity, vMaxVelocity;
	vec4 vColour;
	uint iMinLife, iMaxLife;
	float fMinSize, fMaxSize;

	PETYPE eType = PETYPE::PECUBE;
	vec3 vAcceleration;
	uint iMinEmitt, iMaxEmitt;
	uint iTimer;
};
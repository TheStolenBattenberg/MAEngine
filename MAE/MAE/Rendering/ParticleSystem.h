#pragma once

/**
* Includes
*/
#include <MAE/Core/Types.h>
#include <MAE/Core/Math.h>

#include <MAE/Rendering/Particle.h>
#include <MAE/Rendering/ParticleEmitter.h>
#include <MAE/Rendering/ParticleModifier.h>
#include <MAE/Rendering/Resources/Texture.h>

class ParticleSystem {
public:
	ParticleSystem(class Renderer* renderer);
	~ParticleSystem();

	void EmitterSet(ParticleEmitter* PE);
	ParticleEmitter* EmitterGet();
	void ModifierAdd(ParticleModifier* PM);
	ParticleModifier* ModifierGet(uint ind);

	void Update(uint time);
	void Render();
	void SetTexture(Texture* tex);
	void SetMaxParticles(uint max);
	uint GetMaxParticles();
	uint GetParticleCount();

private:
	std::vector<Particle> vParticles;
	std::vector<ParticleModifier*> vParticleModifiers;

	ParticleEmitter* pEmitter = nullptr;
	uint iMaxParticles;

	class Renderer* pRenderer;
	Texture* pTexture = nullptr;

	LPDIRECT3DVERTEXBUFFER9 d3dVertexBuffer;
	LPDIRECT3DVERTEXDECLARATION9 d3dDecl;
};
#include "Main.h"

ParticleSystem::ParticleSystem(uint particlecount) {
	psParticleCount = particlecount;
}

ParticleSystem::~ParticleSystem() {
	//TO-DO: Destroy Code.
}

float ParticleSystem::randomRange(float floor, float ceiling) {
		srand(5982); //Don't call this every single time. Also change the way seeds are generated.

		float range = (ceiling - floor);
		return floor + int((range * rand()) / (RAND_MAX + 1.0));
}

uint ParticleSystem::addParticle(uint index) {
	Particle part; //There has to be a better way to do this.
	part.pPosition[0] = randomRange(psPositionMin[0], psPositionMax[0]); //Set Position
	part.pPosition[1] = randomRange(psPositionMin[1], psPositionMax[1]);
	part.pPosition[2] = randomRange(psPositionMin[2], psPositionMax[2]);
	part.pVelocity[0] = randomRange(psVelocityMin[0], psVelocityMax[0]); //Set Velocity
	part.pVelocity[1] = randomRange(psVelocityMin[1], psVelocityMax[1]);
	part.pVelocity[2] = randomRange(psVelocityMin[2], psVelocityMax[2]);
	part.pDiffuse[0]  = randomRange(psColourMin[0], psColourMax[0]);     //Set Colour
	part.pDiffuse[1]  = randomRange(psColourMin[1], psColourMax[1]);
	part.pDiffuse[2]  = randomRange(psColourMin[2], psColourMax[2]);
	part.pDiffuse[3]  = randomRange(psColourMin[3], psColourMax[3]);
	part.pAge         = 0;                                               //Set Age to 0
	part.pLife        = randomRange(psLifeMin, psLifeMax);               //Set Life
	part.pSize        = randomRange(psSizeMin, psSizeMax);               //Set Size

	pBuffer[index] = part;
	return index;
}

void ParticleSystem::removeParticle(uint index) {
	pBuffer[index].pAge = pBuffer[index].pLife + 1;
}

void ParticleSystem::updateSystem() {
	for (uint i = 0; i < psParticleCount; ++i) {
		if (pBuffer[i].pAge >= pBuffer[i].pLife) {
			addParticle(i);
		}
		else {
			pBuffer[i].pAge++;
		}
	}

	/**
	 * TO-DO: Add transfer to vertex buffer.
	 */
}

void ParticleSystem::renderSystem() {
	if (pUseAdditiveBlending) { //Set blending to Additive.
		mamain->d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mamain->d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	/**
	 * TO-DO: Render Code
	 */

	if (pUseAdditiveBlending) { //Reset blending to normal.
		mamain->d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		mamain->d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
}

void ParticleSystem::setSystemPosition(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
	psPositionMin[0] = xMin;
	psPositionMin[1] = yMin;
	psPositionMin[2] = zMin;
	psPositionMax[0] = xMax;
	psPositionMax[1] = yMax;
	psPositionMax[2] = zMax;
}

void ParticleSystem::setSystemVelocity(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
	psVelocityMin[0] = xMin;
	psVelocityMin[1] = yMin;
	psVelocityMin[2] = zMin;
	psVelocityMax[0] = xMax;
	psVelocityMax[1] = yMax;
	psVelocityMax[2] = zMax;
}

void ParticleSystem::setSystemColour(float rMin, float gMin, float bMin, float aMin, float rMax, float gMax, float bMax, float aMax) {
	// TO-DO: Colour range.
}

void ParticleSystem::setSystemLife(float lifeMin, float lifeMax) {
	psLifeMin = lifeMin;
	psLifeMax = lifeMax;
}

void ParticleSystem::setSystemSize(float sizeMin, float sizeMax) {
	psSizeMin = sizeMin;
	psSizeMax = sizeMax;
}
void ParticleSystem::setSystemAdditiveBlending(bool truefalse) {
	pUseAdditiveBlending = truefalse;
}
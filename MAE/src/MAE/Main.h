#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/UnorderedVector.h>
#include <MAE/Core/Types.h>

#include <d3d9.h>

class Main: public Releasable {
public:
	virtual void release() = 0;

	virtual class Renderer* createRendererDX9(LPDIRECT3DDEVICE9 device) = 0;

	UnorderedVector<class MD2Model*> MD2Models;
	UnorderedVector<class XModel*>   XModels;
	UnorderedVector<class MPMModel*> MPMModels;

	UnorderedVector<class ParticleSystem*> ParticleSys;
};

Main* MainCreate();

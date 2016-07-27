#pragma once

#include <MAE/Core/Deletable.h>
#include <MAE/Core/UnorderedVector.h>
#include <MAE/Core/Types.h>

#include <d3d9.h>

class Main: public Deletable {
public:
	virtual ~Main() { }

	virtual class Renderer* createRendererDX9(LPDIRECT3DDEVICE9 device) = 0;

	UnorderedVector<class MD2Model*> MD2Models;
	UnorderedVector<class XModel*>   XModels;

	UnorderedVector<class ParticleSystem*> ParticleSys;
};

Main* MainCreate();

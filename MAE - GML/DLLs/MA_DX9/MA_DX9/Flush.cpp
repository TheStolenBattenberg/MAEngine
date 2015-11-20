#include "Flush.h"
#include "Main.h"

Flush::~Flush()
{
	if (vb != 0)
		vb->Release();
}

void Flush::beginFetch()
{
	if (vb != 0)
		vb->Release();

	mamain->hook->enable(Hook::ActionFetchVBCreate);
}

void Flush::endFetch()
{
	mamain->hook->disable(Hook::ActionFetchVBCreate);

	if (mamain->hook->values.empty())
		return;

	if (mamain->hook->values.top().getType() != Variant::TypePointer)
		return;

	vb = (LPDIRECT3DVERTEXBUFFER9) mamain->hook->values.top().getPointer();

	while (!mamain->hook->values.empty())
		mamain->hook->values.pop();

	mamain->hook->set(Hook::PropertyRedirectVBFrom, Variant(vb));
	mamain->hook->enable(Hook::ActionRedirectVertexBuffer);
}

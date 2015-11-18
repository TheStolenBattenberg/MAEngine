#include "Flush.h"
#include "Main.h"

Flush::~Flush()
{
	mamain->hook->disable(Hook::IgnoreVertexBuffer);

	if (vb != 0)
		vb->Release();
}

void Flush::beginFetch()
{
	if (vb != 0)
		vb->Release();

	mamain->hook->enable(Hook::FetchVertexBufferCreate);
}

void Flush::endFetch()
{
	mamain->hook->disable(Hook::FetchVertexBufferCreate);

	if (mamain->hook->values.empty())
		return;

	if (mamain->hook->values.top().getType() != Variant::TypePointer)
		return;

	vb = (LPDIRECT3DVERTEXBUFFER9) mamain->hook->values.top().getPointer();

	while (!mamain->hook->values.empty())
		mamain->hook->values.pop();

	mamain->hook->set(Hook::IgnoreedVertexBuffer, Variant(vb));
	mamain->hook->enable(Hook::IgnoreVertexBuffer);
}

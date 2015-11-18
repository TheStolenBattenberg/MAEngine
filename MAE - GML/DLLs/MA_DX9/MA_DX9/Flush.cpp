#include "Flush.h"
#include "Main.h"

Flush::~Flush()
{
	// mamain.hook->disable(D3DHook::IgnoreVertexBuffer);

	if (vb != 0)
		vb->Release();
}

void Flush::beginFetch()
{
	if (vb != 0)
		vb->Release();

	mamain.hook->enable(D3DHook::FetchVertexBufferCreate);
}

void Flush::endFetch()
{
	mamain.hook->disable(D3DHook::FetchVertexBufferCreate);

	if (mamain.hook->values.empty())
		return;

	if (mamain.hook->values.top().getType() != Variant::TypePointer)
		return;

	vb = (LPDIRECT3DVERTEXBUFFER9) mamain.hook->values.top().getPointer();

	while (!mamain.hook->values.empty())
		mamain.hook->values.pop();

	mamain.hook->set(D3DHook::IgnoreedVertexBuffer, Variant(vb));
	mamain.hook->enable(D3DHook::IgnoreVertexBuffer);
}

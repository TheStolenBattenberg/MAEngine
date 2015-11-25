#include "Main.h"
#include "Types.h"

//Id .MD2 mesh.
DLLEXPORT double MADX9_MD2Load(const char* MD2ModelFile, double texInd)
{
	if ((uint)texInd >= mamain->Textures.size())
		return 0;

	if (mamain->Textures[(uint)texInd] == 0)
		return 0;

	MD2Model* MD2 = new MD2Model();

	if (!MD2->load(MD2ModelFile))
	{
		delete MD2;
		return -1;
	}

	MD2->setTexture(mamain->Textures[(uint)texInd]->tex);

	if (mamain->VertexDeclarationMD2 == 0)
	{
		D3DVERTEXELEMENT9 tween_decl_ve[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
			{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END() // this macro is always needed as the last item! DON'T FORGET ;)
		};

		mamain->d3ddev->CreateVertexDeclaration(tween_decl_ve, &mamain->VertexDeclarationMD2);
	}

	for (size_t i = 0; i < mamain->MD2Models.size(); ++i)
	{
		if (mamain->MD2Models[i] == 0)
		{
			mamain->MD2Models[i] = MD2;
			return i;
		}
	}

	mamain->MD2Models.push_back(MD2);
	return mamain->MD2Models.size() - 1;
}

DLLEXPORT double MADX9_MD2Render(double index, double frame_1, double frame_2, double tween)
{
	if ((uint)index >= mamain->MD2Models.size())
		return 0;

	MD2Model* MD2 = mamain->MD2Models[(uint)index];

	if (frame_1 > MD2->getFrameCount())
		frame_1 = MD2->getFrameCount();
	else if (frame_1 < 0)
		frame_1 = 0;

	if (frame_2 > MD2->getFrameCount())
		frame_2 = MD2->getFrameCount();
	else if (frame_2 < 0)
		frame_2 = 0;

	float t = (float)tween;

	mamain->d3ddev->SetTexture(0, MD2->getTex());

	mamain->d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	mamain->d3ddev->SetRenderState(D3DRS_TWEENFACTOR, *(DWORD*)&t);
	mamain->d3ddev->SetVertexDeclaration(mamain->VertexDeclarationMD2);

	mamain->d3ddev->SetIndices(MD2->getIB());
	mamain->d3ddev->SetStreamSource(0, MD2->getVB((uint)frame_1), 0, sizeof(Vertex));
	mamain->d3ddev->SetStreamSource(1, MD2->getVB((uint)frame_2), 0, sizeof(Vertex));
	mamain->d3ddev->SetStreamSource(2, MD2->getTB(), 0, sizeof(TexCoord));

	mamain->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MD2->getVertCount(), 0, MD2->getTriCount());

	mamain->d3ddev->SetVertexDeclaration(NULL);
	mamain->d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);

	return 1;
}

DLLEXPORT double MADX9_MD2GetFrames(double index)
{
	if ((uint)index >= mamain->MD2Models.size())
		return 0;

	return mamain->MD2Models[(uint)index]->getFrameCount();
}

DLLEXPORT double MADX9_MD2Destroy(double index)
{
	if ((uint)index >= mamain->MD2Models.size())
		return 0;

	delete mamain->MD2Models[(uint)index];
	mamain->MD2Models[(uint)index] = 0;

	return 1;
}


//Microsoft .X mesh.
DLLEXPORT double MADX9_XLoad(const char* XModelFile, const char* TextureDirectory)
{
	XModel* x = new XModel();
	if (!x->load(XModelFile, TextureDirectory)) {
		delete x;
		return -1;
	}

	for (size_t i = 0; i < mamain->XModels.size(); ++i)
	{
		if (mamain->XModels[i] == 0)
		{
			mamain->XModels[i] = x;
			return i;
		}
	}

	mamain->XModels.push_back(x);
	return mamain->XModels.size() - 1;
}

DLLEXPORT double MADX9_XRender(double index)
{
	if ((uint)index > mamain->XModels.size()) {
		return 0;
	}

	XModel* x = mamain->XModels[(uint)index];

	for (uint i = 0; i < x->getMaterialCount(); ++i) {
		mamain->d3ddev->SetMaterial(&x->getMaterial(i));
		mamain->d3ddev->SetTexture(0, x->getTexture(i));
		x->getMesh()->DrawSubset(i);
	}

	return 1;
}

DLLEXPORT double MADX9_XDestroy(double index) 
{
	if ((uint)index > mamain->XModels.size()) {
		return 0;
	}

	delete mamain->XModels[(uint)index];
	mamain->XModels[(uint)index] = 0;
	return 1;
}
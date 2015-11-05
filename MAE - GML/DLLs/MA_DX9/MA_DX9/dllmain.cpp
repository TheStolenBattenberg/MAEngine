#define DLLEXPORT extern "C" __declspec (dllexport)

#include "Main.h"
#include "Types.h"

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	mamain.init(pointer);

	return 1;
}

DLLEXPORT double MADX9_Free()
{
	mamain.free();

	return 1;
}

DLLEXPORT double MADX9_ShaderCreateHLSL9(const char* VSCode, const char* PSCode)
{
	Shader* shd = new Shader();

	//Compile the Shader
	if (!shd->compile(VSCode, PSCode))
	{
		delete shd;
		return -1;
	}

	for (uint i = 0; i < mamain.Shader.size(); ++i)
	{
		if (mamain.Shader[i] == 0)
		{
			mamain.Shader[i] = shd;
			return i;
		}
	}

	mamain.Shader.push_back(shd);
	return mamain.Shader.size() - 1;
}

DLLEXPORT double MADX9_ShaderSetHLSL9(double index)
{
	if ((uint) index > mamain.Shader.size())
		return 0;

	if (mamain.Shader[(uint) index] == 0)
		return 0;

	HRESULT result;

	//Store the current Fixed Vertex Format.
	mamain.d3ddev->GetFVF(&mamain.stFVF);

	//Set the Vertex Shader
	result = mamain.d3ddev->SetVertexShader(mamain.Shader[(uint) index]->VShader);

	if (FAILED(result))
	{
		mamain.err.onErrorDX9("Failed to set vertex shader", result);
		return 0;
	}

	//Set the Pixel Shader
	result = mamain.d3ddev->SetPixelShader(mamain.Shader[(uint) index]->PShader);

	if (FAILED(result))
	{
		mamain.err.onErrorDX9("Failed to set pixel shader", result);
		return 0;
	}

	return 1;
}

DLLEXPORT double MADX9_ShaderResetHLSL9()
{
	HRESULT result;

	//Reset the Vertex Shader.
	result = mamain.d3ddev->SetVertexShader(NULL);

	if (FAILED(result))
		return 0;

	//Reset the Pixel Shader.
	result = mamain.d3ddev->SetPixelShader(NULL);

	if (FAILED(result))
		return 0;

	mamain.d3ddev->SetFVF(mamain.stFVF);
	return 1;
}

DLLEXPORT double MADX9_ShaderDestroyHLSL9(double index)
{
	if ((uint) index > mamain.Shader.size())
		return 0;

	if (mamain.Shader[(uint) index] == 0)
		return 0;

	delete mamain.Shader[(uint) index];
	mamain.Shader[(uint) index] = 0;

	return 1;
}

DLLEXPORT double MADX9_LightCreate(double LightType)
{
	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(Light));

	switch ((int) LightType)
	{
		case 0: Light.Type = D3DLIGHT_POINT; break;
		case 1: Light.Type = D3DLIGHT_SPOT; break;
		case 2: Light.Type = D3DLIGHT_DIRECTIONAL; break;
		default: return -1;
	}

	for (uint i = 0; i < mamain.Light.size(); ++i)
	{
		if (mamain.Light[i].Type == 0)
		{
			mamain.Light[i] = Light;
			return i;
		}
	}

	mamain.Light.push_back(Light);

	return mamain.Light.size() - 1;
}

DLLEXPORT double MADX9_LightDestroy(double index)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint)index].Type = (D3DLIGHTTYPE) 0;

	return 1;
}

DLLEXPORT double MADX9_LightSetAmbient(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation0(double index, double att)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Attenuation0 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation1(double index, double att)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Attenuation1 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation2(double index, double att)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Attenuation2 = (float) att;
	
	return 1;
}

DLLEXPORT double MADX9_LightSetDiffuse(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetDirection(double index, double dx, double dy, double dz)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint)index].Type == 0)
		return 0;

	mamain.Light[(uint)index].Direction = D3DXVECTOR3((float)dx, (float)dy, (float)dz);
	return 1;
}

DLLEXPORT double MADX9_LightSetFalloff(double index, double falloff)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint)index].Type == 0)
		return 0;

	mamain.Light[(uint)index].Falloff = (float)falloff;
	return 1;
}

DLLEXPORT double MADX9_LightSetPhi(double index, double phi)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Phi = D3DXToRadian((float) phi);

	return 1;
}

DLLEXPORT double MADX9_LightSetPosition(double index, double x, double y, double z)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Position = D3DXVECTOR3((float) x, (float) y, (float) z);

	return 1;
}

DLLEXPORT double MADX9_LightSetRange(double index, double range)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Range = (float) range;

	return 1;
}

DLLEXPORT double MADX9_LightSetSpecular(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetTheta(double index, double theta)
{
	if ((uint) index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) index].Type == 0)
		return 0;

	mamain.Light[(uint) index].Theta = D3DXToRadian((float) theta);

	return 1;
}

DLLEXPORT double MADX9_LightEnable(double Index, double LightIndex)
{
	if ((uint) Index >= mamain.Light.size())
		return 0;

	if (mamain.Light[(uint) Index].Type == 0)
		return 0;

	mamain.d3ddev->SetLight((DWORD) Index, &mamain.Light[(uint) LightIndex]);
	mamain.d3ddev->LightEnable((DWORD) Index, TRUE);

	return 1;
}

DLLEXPORT double MADX9_LightDisable(double Index) {
	mamain.d3ddev->LightEnable((DWORD) Index, FALSE);

	return 1;
}

DLLEXPORT double MADX9_MD2Load(const char* MD2ModelFile, const char* MD2TextureFile)
{
	MD2Model* MD2 = new MD2Model();

	if (!MD2->MD2Load(MD2ModelFile, MD2TextureFile))
	{
		mamain.err.onError("Failed to Load MD2 Model");
		
		delete MD2;

		return -1;
	}

	if (mamain.VertexDeclarationMD2 == 0)
	{
		D3DVERTEXELEMENT9 tween_decl_ve[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
			{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END() // this macro is always needed as the last item! DON'T FORGET ;)
		};

		mamain.d3ddev->CreateVertexDeclaration(tween_decl_ve, &mamain.VertexDeclarationMD2);
	}

	for (size_t i = 0; i < mamain.MD2Models.size(); ++i)
	{
		if (mamain.MD2Models[i] == 0)
		{
			mamain.MD2Models[i] = MD2;
			return i;
		}
	}

	mamain.MD2Models.push_back(MD2);
	return mamain.MD2Models.size() - 1;
}

DLLEXPORT double MADX9_MD2Render(double index, double frame_1, double frame_2, double tween)
{
	if ((uint) index >= mamain.MD2Models.size())
		return 0;

	MD2Model* MD2 = mamain.MD2Models[(int) index];

	if (frame_1 > MD2->FetchFrameCount())
		frame_1 = MD2->FetchFrameCount();
	else if (frame_1 < 0)
		frame_1 = 0;

	if (frame_2 > MD2->FetchFrameCount())
		frame_2 = MD2->FetchFrameCount();
	else if (frame_2 < 0)
		frame_2 = 0;

	float t = (float) tween;

	mamain.d3ddev->SetTexture(0, MD2->FetchTexture());

	mamain.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	mamain.d3ddev->SetRenderState(D3DRS_TWEENFACTOR, *(DWORD*) &t);
	mamain.d3ddev->SetVertexDeclaration(mamain.VertexDeclarationMD2);

	mamain.d3ddev->SetIndices(MD2->FetchIB());
	mamain.d3ddev->SetStreamSource(0, MD2->FetchVB((int) frame_1), 0, sizeof(VERTEX));
	mamain.d3ddev->SetStreamSource(1, MD2->FetchVB((int) frame_2), 0, sizeof(VERTEX));
	mamain.d3ddev->SetStreamSource(2, MD2->FetchTB(), 0, sizeof(TEXCOORD));

	mamain.d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MD2->FetchVertexCount(), 0, MD2->FetchTriangleCount());

	mamain.d3ddev->SetVertexDeclaration(NULL);
	mamain.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);

	return 1;
}

DLLEXPORT double MADX9_MD2GetFrames(double index)
{
	if ((uint) index >= mamain.MD2Models.size())
		return 0;

	return mamain.MD2Models[(uint) index]->FetchFrameCount();
}

DLLEXPORT double MADX9_MD2Destroy(double index)
{
	if ((uint) index >= mamain.MD2Models.size())
		return 0;

	delete mamain.MD2Models[(uint) index];
	mamain.MD2Models[(uint) index] = 0;

	return 1;
}

DLLEXPORT double MADX9_HooksCreate()
{
	for (uint i = 0; i < mamain.Hooks.size(); ++i)
	{
		if (mamain.Hooks[i] == 0)
		{
			mamain.Hooks[i] = new D3DHooks(mamain.d3ddev);
			return i;
		}
	}

	mamain.Hooks.push_back(new D3DHooks(mamain.d3ddev));
	return mamain.Hooks.size() - 1;
}

DLLEXPORT double MADX9_HooksDestroy(double ind)
{
	if ((uint) ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint) ind] == 0)
		return 0;

	delete mamain.Hooks[(uint) ind];
	mamain.Hooks[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_HooksApply(double ind, double actions)
{
	if ((uint) ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint) ind] == 0)
		return 0;

	mamain.Hooks[(uint) ind]->apply((D3DHooksActions) (uint) actions);

	return 1;
}

DLLEXPORT double MADX9_HooksRemove(double ind, double actions)
{
	if ((uint) ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint) ind] == 0)
		return 0;

	mamain.Hooks[(uint) ind]->remove((D3DHooksActions)(uint) actions);

	return 1;
}

DLLEXPORT double MADX9_HooksMakeCurrent(double ind)
{
	if ((uint) ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint) ind] == 0)
		return 0;

	mamain.Hooks[(uint) ind]->makeCurrent();

	return 1;
}

DLLEXPORT double MADX9_HooksStackPopPointer(double ind)
{
	if ((uint) ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint) ind] == 0)
		return 0;

	double p;

	memset(&p, 0, sizeof(p));

	if (!mamain.Hooks[(uint) ind]->values.empty())
	{
		*((void**)&p) = mamain.Hooks[(uint) ind]->values.top().getPointer();
		mamain.Hooks[(uint) ind]->values.pop();
	}

	return p;
}

DLLEXPORT double MADX9_HooksStackEmpty(double ind)
{
	if ((uint) ind >= mamain.Hooks.size())
		return -1;

	if (mamain.Hooks[(uint) ind] == 0)
		return -1;

	return mamain.Hooks[(uint) ind]->values.empty();
}

DLLEXPORT double MADX9_HooksStackClear(double ind)
{
	if ((uint) ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint) ind] == 0)
		return 0;

	while (!mamain.Hooks[(uint) ind]->values.empty())
		mamain.Hooks[(uint) ind]->values.pop();

	return 1;
}

DLLEXPORT double MADX9_ErrorSetFlags(double flags) {
	mamain.err.flags = (uint) flags;

	return 1;
}

DLLEXPORT double MADX9_ErrorEmpty() {
	return mamain.err.empty();
}

DLLEXPORT const char* MADX9_ErrorPop() {
	return mamain.returnStr(mamain.err.pop());
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_DETACH:
		if (mamain.isInitialized())
			MessageBox(0, "MADX9 wasn't freed. MAE_Free() should be called at the end.", "MADX9", MB_OK | MB_ICONWARNING);

		break;
	}

	return 1;
}

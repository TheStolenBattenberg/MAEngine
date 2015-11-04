#define DLLEXPORT extern "C" __declspec (dllexport)

#include "dllbackend.h"
#include "Types.h"

/**
 * retStr is used to return strings to game maker
 */

std::string retStr;

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	marb.d3ddev = pointer;
	return 1;
}

DLLEXPORT double MADX9_Free()
{
	for (uint i = 0; i < marb.VShader.size(); ++i)
	{
		if (marb.VShader[i] != 0)
			marb.VShader[i]->Release();

		if (marb.PShader[i] != 0)
			marb.PShader[i]->Release();
	}
	
	marb.VShader.clear();
	marb.PShader.clear();

	for (uint i = 0; i < marb.MD2Models.size(); ++i)
		if (marb.MD2Models[i] != 0)
			delete marb.MD2Models[i];

	marb.MD2Models.clear();

	if (marb.VertexDeclarationMD2 != 0) {
		marb.VertexDeclarationMD2->Release();
		marb.VertexDeclarationMD2 = 0;
	}

	for (uint i = 0; i < marb.Hooks.size(); ++i)
		if (marb.Hooks[i] != 0)
			delete marb.Hooks[i];

	marb.Hooks.clear();

	return 1;
}

DLLEXPORT double MADX9_ShaderCreateHLSL9(const char* VSCode, const char* PSCode)
{
	IDirect3DVertexShader9* VShd;
	IDirect3DPixelShader9*  PShd;

	//Compile the Shader
	if(!marb.HLSL9Compile(VSCode, PSCode, &VShd, &PShd))
		return -1;

	for (uint i = 0; i < marb.VShader.size(); ++i)
	{
		if (marb.VShader[i] == 0)
		{
			marb.VShader[i] = VShd;
			marb.PShader[i] = PShd;
			return i;
		}
	}

	//Add shaders to container and return shader index
	marb.VShader.push_back(VShd);
	marb.PShader.push_back(PShd);

	return marb.PShader.size() - 1;
}

DLLEXPORT double MADX9_ShaderSetHLSL9(double index)
{
	if ((uint) index > marb.VShader.size())
		return 0;

	if (marb.VShader[(uint) index] == 0)
		return 0;

	HRESULT result;

	//Store the current Fixed Vertex Format.
	marb.d3ddev->GetFVF(&marb.stFVF);

	//Set the Vertex Shader
	result = marb.d3ddev->SetVertexShader(marb.VShader[(uint) index]);

	if (FAILED(result))
	{
		marb.err.onErrorDX9("Failed to set vertex shader", result);
		return 0;
	}

	//Set the Pixel Shader
	result = marb.d3ddev->SetPixelShader(marb.PShader[(uint) index]);

	if (FAILED(result))
	{
		marb.err.onErrorDX9("Failed to set pixel shader", result);
		return 0;
	}

	return 1;
}

DLLEXPORT double MADX9_ShaderResetHLSL9()
{
	HRESULT result;

	//Reset the Vertex Shader.
	result = marb.d3ddev->SetVertexShader(NULL);

	if (FAILED(result))
		return 0;

	//Reset the Pixel Shader.
	result = marb.d3ddev->SetPixelShader(NULL);

	if (FAILED(result))
		return 0;

	marb.d3ddev->SetFVF(marb.stFVF);
	return 1;
}

DLLEXPORT double MADX9_ShaderDestroyHLSL9(double index)
{
	if ((uint) index > marb.VShader.size())
		return 0;

	if (marb.VShader[(uint) index] == 0)
		return 0;

	//Delete Vertex Shader
	marb.VShader[(uint) index]->Release();
	marb.VShader[(uint) index] = 0;

	//Delete Pixel Shader
	marb.PShader[(uint) index]->Release();
	marb.PShader[(uint) index] = 0;

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

	for (uint i = 0; i < marb.Light.size(); ++i)
	{
		if (marb.Light[i].Type == 0)
		{
			marb.Light[i] = Light;
			return i;
		}
	}

	marb.Light.push_back(Light);

	return marb.Light.size() - 1;
}

DLLEXPORT double MADX9_LightDestroy(double index)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint)index].Type = (D3DLIGHTTYPE) 0;

	return 1;
}

DLLEXPORT double MADX9_LightSetAmbient(double index, double r, double g, double b, double a)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation0(double index, double att)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Attenuation0 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation1(double index, double att)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Attenuation1 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation2(double index, double att)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Attenuation2 = (float) att;
	
	return 1;
}

DLLEXPORT double MADX9_LightSetDiffuse(double index, double r, double g, double b, double a)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetDirection(double index, double dx, double dy, double dz)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint)index].Type == 0)
		return 0;

	marb.Light[(uint)index].Direction = D3DXVECTOR3((float)dx, (float)dy, (float)dz);
	return 1;
}

DLLEXPORT double MADX9_LightSetFalloff(double index, double falloff)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint)index].Type == 0)
		return 0;

	marb.Light[(uint)index].Falloff = (float)falloff;
	return 1;
}

DLLEXPORT double MADX9_LightSetPhi(double index, double phi)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Phi = D3DXToRadian((float) phi);

	return 1;
}

DLLEXPORT double MADX9_LightSetPosition(double index, double x, double y, double z)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Position = D3DXVECTOR3((float) x, (float) y, (float) z);

	return 1;
}

DLLEXPORT double MADX9_LightSetRange(double index, double range)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Range = (float) range;

	return 1;
}

DLLEXPORT double MADX9_LightSetSpecular(double index, double r, double g, double b, double a)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetTheta(double index, double theta)
{
	if ((uint) index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) index].Type == 0)
		return 0;

	marb.Light[(uint) index].Theta = D3DXToRadian((float) theta);

	return 1;
}

DLLEXPORT double MADX9_LightEnable(double Index, double LightIndex)
{
	if ((uint) Index >= marb.Light.size())
		return 0;

	if (marb.Light[(uint) Index].Type == 0)
		return 0;

	marb.d3ddev->SetLight((DWORD) Index, &marb.Light[(uint) LightIndex]);
	marb.d3ddev->LightEnable((DWORD) Index, TRUE);

	return 1;
}

DLLEXPORT double MADX9_LightDisable(double Index) {
	marb.d3ddev->LightEnable((DWORD) Index, FALSE);

	return 1;
}

DLLEXPORT double MADX9_MD2Load(const char* MD2ModelFile, const char* MD2TextureFile)
{
	MD2Model* MD2 = new MD2Model();

	if (!MD2->MD2Load(MD2ModelFile, MD2TextureFile))
	{
		marb.err.onError("Failed to Load MD2 Model");
		
		delete MD2;

		return -1;
	}

	if (marb.VertexDeclarationMD2 == 0)
	{
		D3DVERTEXELEMENT9 tween_decl_ve[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
			{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END() // this macro is always needed as the last item! DON'T FORGET ;)
		};

		marb.d3ddev->CreateVertexDeclaration(tween_decl_ve, &marb.VertexDeclarationMD2);
	}

	for (size_t i = 0; i < marb.MD2Models.size(); ++i)
	{
		if (marb.MD2Models[i] == 0)
		{
			marb.MD2Models[i] = MD2;
			return i;
		}
	}

	marb.MD2Models.push_back(MD2);
	return marb.MD2Models.size() - 1;
}

DLLEXPORT double MADX9_MD2Render(double index, double frame_1, double frame_2, double tween)
{
	if ((uint) index >= marb.MD2Models.size())
		return 0;

	MD2Model* MD2 = marb.MD2Models[(int) index];

	if (frame_1 > MD2->FetchFrameCount())
		frame_1 = MD2->FetchFrameCount();
	else if (frame_1 < 0)
		frame_1 = 0;

	if (frame_2 > MD2->FetchFrameCount())
		frame_2 = MD2->FetchFrameCount();
	else if (frame_2 < 0)
		frame_2 = 0;

	float t = (float) tween;

	marb.d3ddev->SetTexture(0, MD2->FetchTexture());

	marb.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	marb.d3ddev->SetRenderState(D3DRS_TWEENFACTOR, *(DWORD*) &t);
	marb.d3ddev->SetVertexDeclaration(marb.VertexDeclarationMD2);

	marb.d3ddev->SetIndices(MD2->FetchIB());
	marb.d3ddev->SetStreamSource(0, MD2->FetchVB((int) frame_1), 0, sizeof(VERTEX));
	marb.d3ddev->SetStreamSource(1, MD2->FetchVB((int) frame_2), 0, sizeof(VERTEX));
	marb.d3ddev->SetStreamSource(2, MD2->FetchTB(), 0, sizeof(TEXCOORD));

	marb.d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MD2->FetchVertexCount(), 0, MD2->FetchTriangleCount());

	marb.d3ddev->SetVertexDeclaration(NULL);
	marb.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);

	return 1;
}

DLLEXPORT double MADX9_MD2GetFrames(double index)
{
	if ((uint) index >= marb.MD2Models.size())
		return 0;

	return marb.MD2Models[(uint) index]->FetchFrameCount();
}

DLLEXPORT double MADX9_MD2Destroy(double index)
{
	if ((uint) index >= marb.MD2Models.size())
		return 0;

	delete marb.MD2Models[(uint) index];
	marb.MD2Models[(uint) index] = 0;

	return 1;
}

DLLEXPORT double MADX9_HooksCreate()
{
	for (uint i = 0; i < marb.Hooks.size(); ++i)
	{
		if (marb.Hooks[i] == 0)
		{
			marb.Hooks[i] = new D3DHooks(marb.d3ddev);
			return i;
		}
	}

	marb.Hooks.push_back(new D3DHooks(marb.d3ddev));
	return marb.Hooks.size() - 1;
}

DLLEXPORT double MADX9_HooksDestroy(double ind)
{
	if ((uint) ind >= marb.Hooks.size())
		return 0;

	if (marb.Hooks[(uint) ind] == 0)
		return 0;

	delete marb.Hooks[(uint) ind];
	marb.Hooks[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_HooksApply(double ind, double actions)
{
	if ((uint) ind >= marb.Hooks.size())
		return 0;

	if (marb.Hooks[(uint) ind] == 0)
		return 0;

	marb.Hooks[(uint) ind]->apply((D3DHooksActions) (uint) actions);

	return 1;
}

DLLEXPORT double MADX9_HooksRemove(double ind, double actions)
{
	if ((uint) ind >= marb.Hooks.size())
		return 0;

	if (marb.Hooks[(uint) ind] == 0)
		return 0;

	marb.Hooks[(uint) ind]->remove((D3DHooksActions)(uint) actions);

	return 1;
}

DLLEXPORT double MADX9_HooksMakeCurrent(double ind)
{
	if ((uint) ind >= marb.Hooks.size())
		return 0;

	if (marb.Hooks[(uint) ind] == 0)
		return 0;

	marb.Hooks[(uint) ind]->makeCurrent();

	return 1;
}

DLLEXPORT double MADX9_HooksStackPopPointer(double ind)
{
	if ((uint) ind >= marb.Hooks.size())
		return 0;

	if (marb.Hooks[(uint) ind] == 0)
		return 0;

	double p;

	memset(&p, 0, sizeof(p));

	if (!marb.Hooks[(uint) ind]->values.empty())
	{
		*((void**)&p) = marb.Hooks[(uint) ind]->values.top().getPointer();
		marb.Hooks[(uint) ind]->values.pop();
	}

	return p;
}

DLLEXPORT double MADX9_HooksStackEmpty(double ind)
{
	if (ind < 0 || ind >= marb.Hooks.size())
		return -1;

	if (marb.Hooks[(uint) ind] == 0)
		return -1;

	return marb.Hooks[(uint) ind]->values.empty();
}

DLLEXPORT double MADX9_HooksStackClear(double ind)
{
	if (ind < 0 || ind >= marb.Hooks.size())
		return 0;

	if (marb.Hooks[(uint) ind] == 0)
		return 0;

	while (!marb.Hooks[(uint) ind]->values.empty())
		marb.Hooks[(uint) ind]->values.pop();

	return 1;
}

DLLEXPORT double MADX9_ErrorSetFlags(double flags) {
	marb.err.flags = (uint) flags;

	return 1;
}

DLLEXPORT double MADX9_ErrorEmpty() {
	return marb.err.empty();
}

DLLEXPORT const char* MADX9_ErrorPop() {
	retStr = marb.err.pop();

	return retStr.c_str();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_DETACH:
		/**
		* Free all memory when system unloads DLL
		*/

		MADX9_Free();
		break;
	}

	return 1;
}
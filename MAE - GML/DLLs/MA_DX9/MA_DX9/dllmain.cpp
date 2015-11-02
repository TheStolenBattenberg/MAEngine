#define DLLEXPORT extern "C" __declspec (dllexport)

#include "dllbackend.h"

namespace {
	MADLLBackend MARenderBackend;
}

DLLEXPORT double MADX9_Init(long pointer)
{
	MARenderBackend.d3ddev = (LPDIRECT3DDEVICE9) pointer;
	return 1;
}
DLLEXPORT double MADX9_Free()
{
	int i = MARenderBackend.PShader.size();

	while (i > 0)
	{
		MARenderBackend.PShader[i]->Release();
		MARenderBackend.VShader[i]->Release();
		i--;
	}

	return 1;
}

DLLEXPORT double MADX9_ShaderCreateHLSL9(char* VSCode, char* PSCode)
{
	IDirect3DVertexShader9 *VShd;
	IDirect3DPixelShader9 *PShd;

	//Compile the Shader
	if(MARenderBackend.HLSL9Compile(VSCode, PSCode, &VShd, &PShd) == 0) 
	{ return 0; }

	//Add shaders to container and return shader index;
	MARenderBackend.VShader.push_back(VShd);
	MARenderBackend.PShader.push_back(PShd);
	return MARenderBackend.PShader.size()-1;
}
DLLEXPORT double MADX9_ShaderSetHLSL9(double index)
{
	HRESULT result;

	//Store the current Fixed Vertex Format.
	MARenderBackend.d3ddev->GetFVF(&MARenderBackend.stFVF);

	int ShaderIndex = (int) index;

	//Set the Vertex Shader
	result = MARenderBackend.d3ddev->SetVertexShader(MARenderBackend.VShader[ShaderIndex]);
	if(FAILED(result)) { return 0; }

	//Set the Pixel Shader
	result = MARenderBackend.d3ddev->SetPixelShader(MARenderBackend.PShader[ShaderIndex]);
	if(FAILED(result)) { return 0; }

	return 1;
}
DLLEXPORT double MADX9_ShaderResetHLSL9()
{
	HRESULT result;

	//Reset the Vertex Shader.
	result = MARenderBackend.d3ddev->SetVertexShader(NULL);
	if(FAILED(result)) { return 0; }

	//Reset the Pixel Shader.
	result = MARenderBackend.d3ddev->SetPixelShader(NULL);
	if(FAILED(result)) { return 0; }

	MARenderBackend.d3ddev->SetFVF(MARenderBackend.stFVF);
	return 1;
}
DLLEXPORT double MADX9_ShaderDestroyHLSL9(double index)
{
	int ShaderIndex = (int) index;

	//Delete Vertex Shader
	MARenderBackend.VShader[ShaderIndex]->Release();
	MARenderBackend.VShader.erase(MARenderBackend.VShader.begin() + ShaderIndex);

	//Delete Pixel Shader
	MARenderBackend.PShader[ShaderIndex]->Release();
	MARenderBackend.PShader.erase(MARenderBackend.PShader.begin() + ShaderIndex);

	return 1;
}

DLLEXPORT  double MADX9_LightCreate(double LightType)
{
	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(Light));

	switch ((int) LightType)
	{
		case 0: Light.Type = D3DLIGHT_POINT; break;
		case 1: Light.Type = D3DLIGHT_SPOT; break;
		case 2: Light.Type = D3DLIGHT_DIRECTIONAL; break;
		default: return 0;
	}

	MARenderBackend.Light.push_back(Light);
	return MARenderBackend.Light.size() - 1;
}
DLLEXPORT double MADX9_LightSetAmbient(double index, double r, double g, double b, double a)
{
	MARenderBackend.Light[(int)index].Ambient = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}
DLLEXPORT double MADX9_LightSetAttenuation0(double index, double att)
{
	MARenderBackend.Light[(int)index].Attenuation0 = (float)att;
	return 1;
}
DLLEXPORT double MADX9_LightSetAttenuation1(double index, double att)
{
	MARenderBackend.Light[(int)index].Attenuation1 = (float)att;
	return 1;
}
DLLEXPORT double MADX9_LightSetAttenuation2(double index, double att)
{
	MARenderBackend.Light[(int)index].Attenuation2 = (float)att;
	return 1;
}
DLLEXPORT double MADX9_LightSetDiffuse(double index, double r, double g, double b, double a)
{
	MARenderBackend.Light[(int)index].Diffuse = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}
DLLEXPORT double MADX9_LightSetDirection(double index, double dx, double dy, double dz)
{
	MARenderBackend.Light[(int)index].Direction = D3DXVECTOR3((float)dx, (float)dy, (float)dz);
	return 1;
}
DLLEXPORT double MADX9_LightSetFalloff(double index, double falloff)
{
	MARenderBackend.Light[(int)index].Falloff = (float)falloff;
	return 1;
}
DLLEXPORT double MADX9_LightSetPhi(double index, double phi)
{
	MARenderBackend.Light[(int)index].Phi = D3DXToRadian((float)phi);
	return 1;
}
DLLEXPORT double MADX9_LightSetPosition(double index, double x, double y, double z)
{
	MARenderBackend.Light[(int)index].Position = D3DXVECTOR3((float)x, (float)y, (float)z);
	return 1;
}
DLLEXPORT double MADX9_LightSetRange(double index, double range)
{
	MARenderBackend.Light[(int)index].Range = (float)range;
	return 1;
}
DLLEXPORT double MADX9_LightSetSpecular(double index, double r, double g, double b, double a)
{
	MARenderBackend.Light[(int)index].Specular = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}
DLLEXPORT double MADX9_LightSetTheta(double index, double theta)
{
	MARenderBackend.Light[(int)index].Theta = D3DXToRadian((float)theta);
	return 1;
}
DLLEXPORT double MADX9_LightEnable(double Index, double LightIndex)
{
	MARenderBackend.d3ddev->SetLight((DWORD)Index, &MARenderBackend.Light[(int) LightIndex]);
	MARenderBackend.d3ddev->LightEnable((DWORD)Index, TRUE);
	return 1;
}

DLLEXPORT double MADX9_MD2Load(char* MD2ModelFile, LPCWSTR MD2TextureFile)
{
	MD2Model* MD2 = new MD2Model();

	MD2->MD2Load(MD2ModelFile, MD2TextureFile);
	if (!MD2->IsValid())
	{
		MessageBoxA(NULL, "Failed to Load MD2 Model.", "Error!", MB_ICONERROR);
		return 0;
	}

	D3DVERTEXELEMENT9 tween_decl_ve[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END() // this macro is always needed as the last item! DON'T FORGET ;)
	};
	MARenderBackend.d3ddev->CreateVertexDeclaration(tween_decl_ve, &MARenderBackend.VertexDeclarationMD2);

	MARenderBackend.MD2Models.push_back(MD2);
	return MARenderBackend.MD2Models.size() - 1;
}
DLLEXPORT double MADX9_MD2Render(double index, double frame_1, double frame_2, double tween)
{
	MD2Model* MD2 = MARenderBackend.MD2Models[(int) index];
	if (frame_1 > MD2->FetchFrameCount())
	{
		frame_1 = 0;
	}
	if (frame_2 > MD2->FetchFrameCount())
	{
		frame_2 = 0;
	}

	MARenderBackend.d3ddev->SetTexture(0, MD2->FetchTexture());

	MARenderBackend.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	MARenderBackend.d3ddev->SetRenderState(D3DRS_TWEENFACTOR, (DWORD) tween);
	MARenderBackend.d3ddev->SetVertexDeclaration(MARenderBackend.VertexDeclarationMD2);

	MARenderBackend.d3ddev->SetIndices(MD2->FetchIB());
	MARenderBackend.d3ddev->SetStreamSource(0, MD2->FetchVB((int) frame_1), 0, sizeof(MD2_POSITION_VERTEX));
	MARenderBackend.d3ddev->SetStreamSource(1, MD2->FetchVB((int) frame_2), 0, sizeof(MD2_POSITION_VERTEX));
	MARenderBackend.d3ddev->SetStreamSource(2, MD2->FetchTB(), 0, sizeof(MD2_TEXTURE_VERTEX));

	MARenderBackend.d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MD2->FetchVertexCount(), 0, MD2->FetchTriangleCount());

	MARenderBackend.d3ddev->SetVertexDeclaration(NULL);
	MARenderBackend.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
	return 1;
}
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

DLLEXPORT double MADX9_ShaderFindConstant(double index, double shd, const char* c)
{
	if ((uint) index >= mamain.Shader.size())
		return -1;

	if (mamain.Shader[(uint) index] == 0)
		return -1;

	ShaderConstants* t = shd ? &mamain.Shader[(uint) index]->PConstants : &mamain.Shader[(uint) index]->VConstants;

	return t->find(c);
}

DLLEXPORT double MADX9_ShaderSetConstantVec3(double index, double shd, double c, double x, double y, double z)
{
	if ((uint) index >= mamain.Shader.size())
		return -1;

	if (mamain.Shader[(uint) index] == 0)
		return -1;

	ShaderConstants* t = shd ? &mamain.Shader[(uint) index]->PConstants : &mamain.Shader[(uint) index]->VConstants;

	vec3 v = {(float) x, (float) y, (float) z};

	return t->setVec3((uint) c, v);
}

DLLEXPORT double MADX9_ShaderSetConstantVec4(double index, double shd, double c, double x, double y, double z, double w)
{
	if ((uint) index >= mamain.Shader.size())
		return -1;

	if (mamain.Shader[(uint) index] == 0)
		return -1;

	ShaderConstants* t = shd ? &mamain.Shader[(uint) index]->PConstants : &mamain.Shader[(uint) index]->VConstants;

	vec4 v = {(float) x, (float) y, (float) z, (float) w};

	return t->setVec4((uint) c, v);
}

DLLEXPORT double MADX9_ShaderSetConstantMat3(double index, double shd, double c)
{
	if ((uint) index >= mamain.Shader.size())
		return -1;

	if (mamain.Shader[(uint) index] == 0)
		return -1;

	ShaderConstants* t = shd ? &mamain.Shader[(uint) index]->PConstants : &mamain.Shader[(uint) index]->VConstants;

	mat3 v;

	memcpy(v, mamain.matStack.data(), sizeof(v));

	return t->setMat3((uint) c, v);
}

DLLEXPORT double MADX9_ShaderSetConstantMat4(double index, double shd, double c)
{
	if ((uint) index >= mamain.Shader.size())
		return -1;

	if (mamain.Shader[(uint) index] == 0)
		return -1;

	ShaderConstants* t = shd ? &mamain.Shader[(uint) index]->PConstants : &mamain.Shader[(uint) index]->VConstants;

	mat4 v;

	memcpy(v, mamain.matStack.data(), sizeof(v));

	return t->setMat4((uint) c, v);
}

DLLEXPORT double MADX9_MaterialCreate()
{
	D3DMATERIAL9 Material;
	ZeroMemory(&Material, sizeof(Material));

	for (uint i = 0; i < mamain.Material.size(); ++i)
	{
		if (mamain.Material[i].Power == -1.0f)
		{
			mamain.Material[i] = Material;
			return i;
		}
	}

	mamain.Material.push_back(Material);
	return mamain.Material.size() - 1;
}

DLLEXPORT double MADX9_MaterialDestroy(double index)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	//Find a better way to 'destroy' materials. Maybe a new resource type with a bool? Same for lights.
	mamain.Material[(uint)index].Power = -1.0f;
	
	return 1;
}

DLLEXPORT double MADX9_MaterialSetDiffuse(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint) index].Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSetAmbient(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Ambient = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSetSpecular(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Specular = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSetSpecularPower(double index, double p)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Power = (float)p;
	return 1;
}

DLLEXPORT double MADX9_MaterialSetEmissive(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Emissive = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSet(double index)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.d3ddev->SetMaterial(&mamain.Material[(uint)index]);
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

DLLEXPORT double MADX9_MD2Load(const char* MD2ModelFile, double texInd)
{
	if ((uint) texInd >= mamain.Textures.size())
		return 0;

	if (mamain.Textures[(uint) texInd] == 0)
		return 0;

	MD2Model* MD2 = new MD2Model();

	if (!MD2->load(MD2ModelFile))
	{
		delete MD2;
		return -1;
	}

	MD2->setTexture(mamain.Textures[(uint) texInd]->tex);

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

	MD2Model* MD2 = mamain.MD2Models[(uint) index];

	if (frame_1 > MD2->getFrameCount())
		frame_1 = MD2->getFrameCount();
	else if (frame_1 < 0)
		frame_1 = 0;

	if (frame_2 > MD2->getFrameCount())
		frame_2 = MD2->getFrameCount();
	else if (frame_2 < 0)
		frame_2 = 0;

	float t = (float) tween;

	mamain.d3ddev->SetTexture(0, MD2->getTex());

	mamain.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	mamain.d3ddev->SetRenderState(D3DRS_TWEENFACTOR, *(DWORD*) &t);
	mamain.d3ddev->SetVertexDeclaration(mamain.VertexDeclarationMD2);

	mamain.d3ddev->SetIndices(MD2->getIB());
	mamain.d3ddev->SetStreamSource(0, MD2->getVB((uint) frame_1), 0, sizeof(Vertex));
	mamain.d3ddev->SetStreamSource(1, MD2->getVB((uint) frame_2), 0, sizeof(Vertex));
	mamain.d3ddev->SetStreamSource(2, MD2->getTB(), 0, sizeof(TexCoord));

	mamain.d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MD2->getVertCount(), 0, MD2->getTriCount());

	mamain.d3ddev->SetVertexDeclaration(NULL);
	mamain.d3ddev->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);

	return 1;
}

DLLEXPORT double MADX9_MD2GetFrames(double index)
{
	if ((uint) index >= mamain.MD2Models.size())
		return 0;

	return mamain.MD2Models[(uint) index]->getFrameCount();
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

DLLEXPORT double MADX9_TextureCreateFromFile(const char* file, Texture::MipMaps mipmaps)
{
	Texture* tex = new Texture();

	if (!tex->loadFromFile(file, mipmaps))
	{
		delete tex;
		return -1;
	}

	for (uint i = 0; i < mamain.Textures.size(); ++i)
	{
		if (mamain.Textures[i] == 0)
		{
			mamain.Textures[i] = tex;
			return i;
		}
	}

	mamain.Textures.push_back(tex);
	return mamain.Textures.size() - 1;
}

DLLEXPORT double MADX9_TextureCreateFromPointer(double ptr)
{
	Texture* tex = new Texture();

	memcpy(&tex->tex, &ptr, sizeof(tex->tex));

	if (tex->tex == 0)
	{
		delete tex;
		return -1;
	}

	tex->tex->AddRef();

	for (uint i = 0; i < mamain.Textures.size(); ++i)
	{
		if (mamain.Textures[i] == 0)
		{
			mamain.Textures[i] = tex;
			return i;
		}
	}

	mamain.Textures.push_back(tex);
	return mamain.Textures.size() - 1;
}

DLLEXPORT double MADX9_TextureDestroy(double ind)
{
	if ((uint) ind >= mamain.Textures.size())
		return 0;

	if (mamain.Textures[(uint) ind] == 0)
		return 0;

	delete mamain.Textures[(uint) ind];
	mamain.Textures[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_TextureSet(double ind, double stage)
{
	if (ind < 0)
		return SUCCEEDED(mamain.d3ddev->SetTexture((uint) stage, 0));

	if ((uint) ind >= mamain.Textures.size())
		return 0;

	if (mamain.Textures[(uint) ind] == 0)
		return 0;

	return SUCCEEDED(mamain.d3ddev->SetTexture((uint) stage, mamain.Textures[(uint) ind]->tex));
}

DLLEXPORT double MADX9_SamplerSetState(double stage, double type, double value)
{
	return SUCCEEDED(mamain.d3ddev->SetSamplerState((uint) stage, (D3DSAMPLERSTATETYPE) (uint) type, (uint) value));
}

DLLEXPORT double MADX9_RenderSetState(double state, double value)
{
	uint v;

	switch ((D3DRENDERSTATETYPE) (uint) state)
	{
	case D3DRS_FOGSTART:
	case D3DRS_FOGEND:
	case D3DRS_FOGDENSITY:
	case D3DRS_POINTSIZE:
	case D3DRS_POINTSIZE_MIN:
	case D3DRS_POINTSCALE_A:
	case D3DRS_POINTSCALE_B:
	case D3DRS_POINTSCALE_C:
	case D3DRS_PATCHEDGESTYLE:
	case D3DRS_POINTSIZE_MAX:
	case D3DRS_TWEENFACTOR:
	case D3DRS_DEPTHBIAS:
		*(float*) &v = (float) value;
		break;
	default:
		v = (uint) value;
		break;
	}

	return SUCCEEDED(mamain.d3ddev->SetRenderState((D3DRENDERSTATETYPE) (uint) state, v));
}

DLLEXPORT double MADX9_MatStackFloat(double v1, double v2, double v3, double v4)
{
	mamain.matStack.push_back((float) v1);
	mamain.matStack.push_back((float) v2);
	mamain.matStack.push_back((float) v3);
	mamain.matStack.push_back((float) v4);

	return 1;
}

DLLEXPORT double MADX9_MatStackClear()
{
	mamain.matStack.clear();

	return 1;
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

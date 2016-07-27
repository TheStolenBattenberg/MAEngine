#include <MAE/Rendering/Pipeline/ForwardPipeline.h>

#include <cassert>

ForwardPipelineShader::ForwardPipelineShader(Renderer* renderer) {
	m_shader = renderer->createShader(
		"uniform float4x4 uMVP    : register(c0);"
		"uniform float3x3 uNormal : register(c4);"
		""
		"struct VS_INPUT {"
		"    float3 position : POSITION;"
		"    float3 normal   : NORMAL0;"
		"    float2 texcoord : TEXCOORD0;"
		"};"
		""
		"struct VS_OUTPUT {"
		"    float4 position : POSITION;"
		"    float2 texcoord : TEXCOORD0;"
		"    float3 normal   : TEXCOORD1;"
		"};"
		""
		"VS_OUTPUT main(VS_INPUT input) {"
		"    VS_OUTPUT output;"
		""
		"    output.texcoord = input.texcoord;"
		"    output.normal   = mul(uNormal, input.normal);"
		""
		"    output.position = mul(uMVP, float4(input.position, 1.0));"
		""
		"    return output;"
		"}"
		,
		"uniform float4 uAmbientColor : register(c0);"
		"uniform float3 uLightDir     : register(c1);"
		""
		"uniform sampler2D uTex : register(s0);"
		""
		"struct PS_INPUT {"
		"    float2 texcoord : TEXCOORD0;"
		"    float3 normal   : TEXCOORD1;"
		"};"
		""
		"struct PS_OUTPUT {"
		"    float4 color : COLOR0;"
		"};"
		""
		"PS_OUTPUT main(PS_INPUT input) {"
		"    float4 diffuseColor = tex2D(uTex, input.texcoord);"
		""
		"    PS_OUTPUT output;"
		""
		"    output.color = float4(uAmbientColor.xyz + max(dot(uLightDir, normalize(input.normal)), 0.0) * diffuseColor.xyz, diffuseColor.w);"
		""
		"    return output;"
		"}"
	);

	m_uMVP          = m_shader->find("uMVP");
	m_uNormal       = m_shader->find("uNormal");
	m_uAmbientColor = m_shader->find("uAmbientColor");
	m_uLightDir     = m_shader->find("uLightDir");
	m_uTex          = m_shader->find("uTex");
}

ForwardPipelineShader::~ForwardPipelineShader() {
	delete m_shader;
}

uint ForwardPipelineShader::getLocation(uint loc) {
	const char* table[] = {
		"POSITION", "NORMAL", "TEXCOORD"
	};

	assert(("Invalid loc", loc < sizeof(table) / sizeof(char*)));

	return m_shader->getLocation(table[loc]);
}

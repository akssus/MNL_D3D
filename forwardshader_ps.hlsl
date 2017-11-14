Texture2D Textures[1];
SamplerState Sampler;

cbuffer LightBuffer : register(b0)
{
	float3 lightPos;
	float3 lightDir;
	uint lightType;
};

cbuffer MaterialBuffer : register(b1)
{
	float4 diffuse;
	float4 ambient;
	float4 emissive;
	float4 specular;
	float specularPower;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
	float3 lightDir : TEXCOORD1;
	float3 lightReflect : TEXCOORD2;
	float3 dirToCam : TEXCOORD3;
};

float4 PS_MAIN(PS_INPUT input) : SV_TARGET
{
	float4 blendColor;
	float4 textureColor = Textures[0].Sample(Sampler, input.texCoord);
	float intensity = dot(-input.lightDir, input.normal);
	blendColor = saturate(diffuse * textureColor);
	blendColor = saturate(blendColor * intensity);
	
	//float3 dirToCam = normalize(-input.position.xyz);
	float highlight = 0.0f;
	if (intensity > 0)
	{
		highlight = saturate(dot(input.lightReflect, input.dirToCam));
		highlight = pow(highlight, specularPower);
	}
	float4 specularColor = specular * highlight;

	blendColor = blendColor + ambient +specularColor;
	blendColor.a = 1.0f;

	//blendColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return blendColor;
}
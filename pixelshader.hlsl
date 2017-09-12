Texture2D Textures[1];
SamplerState Sampler;

struct PS_INPUT
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

float4 PS_MAIN(PS_INPUT input) : SV_TARGET
{
	float3 fakeLightDir = float3(0.0f,0.0f,1.0f);
	float4 blendColor;
	float4 textureColor = Textures[0].Sample(Sampler, input.texCoord);

	float intensity = dot(fakeLightDir, input.normal);

	blendColor = saturate(textureColor * intensity);

	return blendColor;
}
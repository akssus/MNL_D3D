
struct PS_INPUT
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
};

float4 PS_MAIN(PS_INPUT input) : SV_TARGET
{
	float3 fakeLightDir = float3(0.0f,0.0f,1.0f);
	float4 blendColor;

	float intensity = dot(fakeLightDir, input.normal);
	intensity = saturate(intensity);

	blendColor = float4(intensity, intensity, intensity, 1.0f);

	return blendColor;
}
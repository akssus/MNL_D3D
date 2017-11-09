Texture2D shaderTexture : register(t0);
SamplerState SampleType;

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


float4 PS_MAIN(PixelInputType input) : SV_TARGET
{
    float4 textureColor;

    textureColor = shaderTexture.Sample(SampleType, input.tex);
	//float xx = input.tex.x;
	//float yy = input.tex.y;
	//textureColor = float4(xx, yy, 1.0f, 1.0f);
	//textureColor = float4(0.5f, 0.5f, 0.5f, 0.5f);

    return textureColor;
}
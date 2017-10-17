Texture2D shaderTexture;
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
	//textureColor = float4(0.5f, 0.5f, 0.5f, 0.5f);

    return textureColor;
}

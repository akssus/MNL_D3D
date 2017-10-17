struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelInputType VS_MAIN(VertexInputType input)
{
    PixelInputType output;
    
    input.position.w = 1.0f;
	output.position = input.position;
    output.tex = input.tex;
    
    return output;
}

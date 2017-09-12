
cbuffer WorldBuffer
{
    matrix worldMatrix;
};

cbuffer ViewProjectionBuffer
{
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};


VS_OUTPUT VS_MAIN(VS_INPUT input)
{
    VS_OUTPUT output;
    
    input.position.w = 1.0f;

    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix); 

	output.normal = mul(input.normal,worldMatrix);
	output.normal = mul(output.normal, viewMatrix);
	output.normal = normalize(output.normal);

	output.texCoord = input.texCoord;
    
    return output;
}

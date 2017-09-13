
cbuffer WorldBuffer : register(b0)
{
    matrix worldMatrix;
};

cbuffer ViewProjectionBuffer : register(b1)
{
	matrix viewMatrix;
	matrix projectionMatrix;
};
cbuffer LightBuffer : register(b2)
{
	float3 lightPos;
	float3 lightDir;
	uint lightType;
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
	float2 texCoord : TEXCOORD0;
	float3 lightDir : TEXCOORD1;
	float3 lightReflect : TEXCOORD2;
	float3 dirToCam : TEXCOORD3;
};


VS_OUTPUT VS_MAIN(VS_INPUT input)
{
    VS_OUTPUT output;
    
    input.position.w = 1.0f;

    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
	float3 viewPos = output.position;
    output.position = mul(output.position, projectionMatrix); 

	output.normal = mul(input.normal,worldMatrix);
	output.normal = mul(output.normal, viewMatrix);
	output.normal = normalize(output.normal);

	output.texCoord = input.texCoord;

	output.lightDir = mul(lightDir, viewMatrix);
	output.lightDir = normalize(output.lightDir);

	output.lightReflect = reflect(output.lightDir, output.normal);
    
	output.dirToCam = normalize(-viewPos);

    return output;
}

#include "UniversalVertexType.h"

using namespace MNL;

UniversalVertexType::UniversalVertexType()
{
	this->AddInputElement(MnInputElement("POSITION", MN_INPUT_ELEMENT_TYPE_FLOAT3,0));
	this->AddInputElement(MnInputElement("COLOR", MN_INPUT_ELEMENT_TYPE_FLOAT4, 0));
	this->AddInputElement(MnInputElement("NORMAL", MN_INPUT_ELEMENT_TYPE_FLOAT3,0));
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2,0));
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2,1));
}


UniversalVertexType::~UniversalVertexType()
{
}

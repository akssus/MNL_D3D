#include "MnMeshVertexType.h"

using namespace MNL;

MnMeshVertexType::MnMeshVertexType()
{
	this->AddInputElement(MnInputElement("POSITION", MN_INPUT_ELEMENT_TYPE_FLOAT3, 0));
	this->AddInputElement(MnInputElement("NORMAL", MN_INPUT_ELEMENT_TYPE_FLOAT3, 0));
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2, 0));
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2, 1));
}


MnMeshVertexType::~MnMeshVertexType()
{
}

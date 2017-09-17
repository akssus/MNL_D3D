#include "MnSkinnedMeshVertexType.h"

using namespace MNL;

MnSkinnedMeshVertexType::MnSkinnedMeshVertexType()
{
	this->AddInputElement(MnInputElement("POSITION", MN_INPUT_ELEMENT_TYPE_FLOAT3, 0));
	this->AddInputElement(MnInputElement("NORMAL", MN_INPUT_ELEMENT_TYPE_FLOAT3, 0));
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2, 0));
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT4, 1), MN_CVF_BONE_INDEX);// bone indices
	this->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT4, 2), MN_CVF_BONE_WEIGHT);// bone weight
}


MnSkinnedMeshVertexType::~MnSkinnedMeshVertexType()
{
}

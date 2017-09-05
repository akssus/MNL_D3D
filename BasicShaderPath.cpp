#include "BasicShaderPath.h"
#include <memory>

using namespace MNL;

BasicShaderPath::BasicShaderPath()
{

}


BasicShaderPath::~BasicShaderPath()
{
}

HRESULT BasicShaderPath::Init(const CPD3DDevice& cpDevice)
{

}

void BasicShaderPath::_InitConstantBuffers(const CPD3DDevice& cpDevice)
{
	MnConstantBufferType transformBufferType;
	transformBufferType.AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	transformBufferType.AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	transformBufferType.AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	m_transformBuffer.Init(cpDevice,)
}
#include "MnInputLayout.h"

using namespace MNL;

MnInputLayout::MnInputLayout()
{
}


MnInputLayout::~MnInputLayout()
{
}

bool MnInputLayout::Init(CPD3DDevice cpD3DDevice, std::shared_ptr<MnCustomVertexType> pCustomVertexType, std::shared_ptr<MnVertexShader> pVertexShader)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescs;
	UINT numInputElements = pCustomVertexType->NumElements();

	for (int i=0; i<numInputElements; ++i)
	{
		inputLayoutDescs.push_back(pCustomVertexType->GetElement(i).GetDesc());
	}

	CPD3DInputLayout cpInputLayout;
	HRESULT result = cpD3DDevice->CreateInputLayout(inputLayoutDescs.data(),
		numInputElements, pVertexShader->GetByteCode()->GetBufferPointer(),
		pVertexShader->GetByteCode()->GetBufferSize(),
		&cpInputLayout);
	if (FAILED(result))
	{
		//error log
		return false;
	}
	m_inputLayout = cpInputLayout;
	return true;;
}
CPD3DInputLayout MnInputLayout::GetInputLayout() const
{
	return m_inputLayout;
}
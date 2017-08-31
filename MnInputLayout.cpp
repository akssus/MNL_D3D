#include "MnInputLayout.h"

using namespace MNL;

MnInputLayout::MnInputLayout()
{
}


MnInputLayout::~MnInputLayout()
{
}

void MnInputLayout::Init(CPD3DDevice cpD3DDevice, std::shared_ptr<MnCustomVertexType> pCustomVertexType, std::shared_ptr<MnVertexShader> pVertexShader)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescs;
	for (auto& inputElement : m_inputElements)
	{
		inputLayoutDescs.push_back(inputElement.GetDesc());
	}
	UINT numElements = m_inputElements.size();

	CPD3DInputLayout cpInputLayout;
	HRESULT result = cpDevice->CreateInputLayout(inputLayoutDescs.data(),
		numElements, pVertexShader->GetByteCode()->GetBufferPointer(),
		pVertexShader->GetByteCode()->GetBufferSize(),
		&cpInputLayout);
	if (FAILED(result))
	{
		//error log
		return nullptr;
	}

	return cpInputLayout;
}
CPD3DInputLayout MnInputLayout::GetInputLayout() const
{

}
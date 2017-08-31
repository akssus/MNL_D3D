#include <memory>
#include "MnCustomVertexType.h"

using namespace MNL;

MnCustomVertexType::MnCustomVertexType():m_totalByteSize(0)
{
}


MnCustomVertexType::~MnCustomVertexType()
{
}

void MnCustomVertexType::AddInputElement(const MnInputElement& inputElement)
{
	m_inputElements.push_back(inputElement);
	m_totalByteSize += inputElement.GetByteSize();
}

MnInputElement MnCustomVertexType::GetElement(UINT index) const
{
	return m_inputElements[index];
}
UINT MnCustomVertexType::TotalByteSize() const
{
	return m_totalByteSize;
}
UINT MnCustomVertexType::NumElements() const
{
	return m_inputElements.size();
}
CPD3DInputLayout MnCustomVertexType::CreateInputLayout(CPD3DDevice cpDevice, std::shared_ptr<MnVertexShader> pVertexShader)
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
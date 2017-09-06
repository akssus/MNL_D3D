#include "MnInputLayout.h"

using namespace MNL;

MnInputLayout::MnInputLayout()
{
}


MnInputLayout::~MnInputLayout()
{
}

HRESULT MnInputLayout::Init(CPD3DDevice cpD3DDevice, const std::shared_ptr<MnCustomVertexType> pCustomVertexType, const std::shared_ptr<MnVertexShader> pVertexShader)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescs;
	UINT numInputElements = pCustomVertexType->NumElements();


	for (int i=0; i<numInputElements; ++i)
	{
		const MnInputElement& inputElement = pCustomVertexType->GetElement(i);
		D3D11_INPUT_ELEMENT_DESC desc = _CreateInputElementDesc(inputElement);
		if (i == 0)
		{
			desc.AlignedByteOffset = 0;
		}
		inputLayoutDescs.push_back(desc);
	}

	CPD3DInputLayout cpInputLayout;
	HRESULT result = cpD3DDevice->CreateInputLayout(inputLayoutDescs.data(),
		numInputElements, (void*)pVertexShader->GetByteCode()->GetBufferPointer(),
		pVertexShader->GetByteCode()->GetBufferSize(),
		cpInputLayout.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	m_inputLayout = cpInputLayout;
	return S_OK;
}

CPD3DInputLayout MnInputLayout::GetInputLayout() const
{
	return m_inputLayout;
}

D3D11_INPUT_ELEMENT_DESC MnInputLayout::_CreateInputElementDesc(const MnInputElement& inputElement)
{
	D3D11_INPUT_ELEMENT_DESC desc;
	desc.SemanticName = inputElement.GetSemanticName().c_str();
	//desc.SemanticName = "test";
	desc.Format = inputElement.GetDXGIFormat();
	desc.SemanticIndex = inputElement.GetIndex();
	desc.InputSlot = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;
	desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	return desc;
}
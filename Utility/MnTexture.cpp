#include "MnTexture.h"

using namespace MNL;

MnTexture::MnTexture()
{
}


MnTexture::~MnTexture()
{
}


HRESULT MnTexture::LoadFromFile(std::wstring textureFileName)
{


	return S_OK;
}

const CPD3DShaderResourceView MnTexture::GetShaderResourceView() const
{
	return m_cpShaderResourceView;
}
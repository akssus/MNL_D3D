#include "MnMeshTexture.h"
#include "Core/MnLog.h"

using namespace MNL;

MnMeshTexture::MnMeshTexture()
{
}


MnMeshTexture::~MnMeshTexture()
{
}


HRESULT MnMeshTexture::LoadFromFile(const CPD3DDevice& cpDevice, const std::wstring& textureFileName)
{
	HRESULT result = DirectX::CreateWICTextureFromFile(cpDevice.Get(),textureFileName.c_str(), nullptr, m_cpShaderResourceView.ReleaseAndGetAddressOf(), 4096);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpShaderResourceView));
		return result;
	}
	return S_OK;
}

const CPD3DShaderResourceView MnMeshTexture::GetShaderResourceView() const
{
	return m_cpShaderResourceView;
}
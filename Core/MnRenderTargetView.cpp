#include "MnRenderTargetView.h"
#include "MnLog.h"

using namespace MNL;

MnRenderTargetView::MnRenderTargetView()
{
}


MnRenderTargetView::~MnRenderTargetView()
{
}

HRESULT MnRenderTargetView::Init(const CPD3DDevice cpDevice, const CPD3DTexture2D renderSurface, const std::shared_ptr<D3D11_RENDER_TARGET_VIEW_DESC> pRenderTargetViewDesc)
{
	HRESULT result = cpDevice->CreateRenderTargetView(renderSurface.Get(), pRenderTargetViewDesc.get(), m_cpRenderTargetView.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpRenderTargetView));
		return result;
	}

	return S_OK;
}
const CPD3DRenderTargetView& MnRenderTargetView::GetRenderTargetView() const
{
	return m_cpRenderTargetView;
}

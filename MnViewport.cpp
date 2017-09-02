#include "MnViewport.h"

using namespace MNL;

MnViewport::MnViewport()
{
}


MnViewport::~MnViewport()
{
}



HRESULT MnViewport::Init(float x, float y, float width, float height)
{
	ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
	m_viewport.Width = width;
	m_viewport.Height = height;
	m_viewport.TopLeftX = x;
	m_viewport.TopLeftY = y;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	return S_OK;
}

const D3D11_VIEWPORT MnViewport::GetViewport() const
{
	return m_viewport;
}
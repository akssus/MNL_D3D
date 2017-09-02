#include "MnDisplayDevice.h"
#include <algorithm>
#include "DXTK\SimpleMath.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnDisplayDevice::MnDisplayDevice()
{
}


MnDisplayDevice::~MnDisplayDevice()
{
}

HRESULT MnDisplayDevice::Init(CPDXGIOutput cpOutput)
{
	UINT numModes = 0;
	//get number of modes with 32bit color
	HRESULT result = cpOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	m_numDisplayModes = numModes;

	m_displayModes.reserve(numModes);
	m_displayModeDescs.reserve(numModes);
	result = cpOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, m_displayModeDescs.data);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	for (int i = 0; i < numModes; ++i)
	{
		m_displayModes[i].width = m_displayModeDescs[i].Width;
		m_displayModes[i].height = m_displayModeDescs[i].Height;
		m_displayModes[i].numerator = m_displayModeDescs[i].RefreshRate.Numerator;
		m_displayModes[i].denominator = m_displayModeDescs[i].RefreshRate.Denominator;
	}

	return S_OK;
}

const CPDXGIOutput MnDisplayDevice::GetInterface() const
{
	return m_cpDXGIOutput;
}
MnDisplayMode MnDisplayDevice::GetClosestMode(UINT width, UINT height, UINT numerator, UINT denominator) const
{
	MnDisplayMode closestMode;
	ZeroMemory(&closestMode, sizeof(MnDisplayMode));

	Vector4 targetSize(width,height,numerator,denominator);
	float minDist = 100000.0f;

	for (MnDisplayMode mode : m_displayModes)
	{
		Vector4 comparedSize(mode.width, mode.height,mode.numerator,mode.denominator);
		float dist =  Vector4::Distance(targetSize, comparedSize);
		if (dist < minDist)
		{
			closestMode = mode;
			minDist = dist;
		}
	}

	return closestMode;
}
bool MnDisplayDevice::IsSupportResolutionOf(UINT width, UINT height) const
{
	bool isSupported;
	for (MnDisplayMode mode : m_displayModes)
	{
		if (mode.width == width && mode.height == height)
		{
			isSupported = true;
			break;
		}
	}
	return isSupported;
}

UINT MnDisplayDevice::GetNumDisplayModes() const
{
	return m_numDisplayModes;
}
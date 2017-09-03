#include "MnDisplayDevice.h"
#include <algorithm>

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

	m_displayModes.resize(numModes);
	m_displayModeDescs.resize(numModes);
	result = cpOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, m_displayModeDescs.data());
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

	Vector2 targetSize(width,height);
	Vector2 targetRate(numerator, denominator);
	UINT minDist = 100000;
	std::vector<MnDisplayMode> minSizes;

	//find closest resolution first
	for (MnDisplayMode mode : m_displayModes)
	{
		Vector2 comparedSize(mode.width, mode.height);
		UINT dist =  Vector2::Distance(targetSize, comparedSize);
		if (dist < minDist)
		{
			minSizes.clear();
			minSizes.push_back(mode);
			minDist = dist;
		}
		else if (dist == minDist)
		{
			minSizes.push_back(mode);
		}
	}

	minDist = 100000;
	//find closest refresh rate among closest resolution modes
	for (MnDisplayMode& mode : minSizes)
	{
		Vector2 comparedRate(mode.numerator, mode.denominator);
		UINT dist = Vector2::Distance(targetRate, comparedRate);
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
/**
@class MNL::MnVideoAdapter
@author Akssus
@brief 비디오 어댑터의 정보와 디스플레이 장치들을 저장한다.

@section 개요
하나의 MnVideoAdapter는 하나의 비디오카드 정보를 담고 있다.\n
비디오 카드의 이름, 비디오 카드 메모리, GPU의 최대 지원 Feature Level 의 정보를 제공한다.\n
*/

#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"
#include "MnDisplayDevice.h"

namespace MNL
{
	/*
	one IDXGIAdapter represnets one MnVideoAdapter instance
	*/
	class MnVideoAdapter
	{
	public:
		MnVideoAdapter();
		~MnVideoAdapter();

		/**
		@brief CPDXGIAdapter 인터페이스를 통해 디스플레이 장치들의 정보를 열거하여 초기화 한다.
		@param cpAdapter IDXGIFactory를 통해 생성된 IDXGIAdapter 인터페이스.
		@return 초기화 성공 여부.
		*/
		HRESULT Init(CPDXGIAdapter cpAdapter);

		/**
		@brief 비디오 어댑터의 이름을 반환한다
		*/
		std::wstring GetName() const;

		/**
		@brief 비디오 어댑터의 비디오 메모리 크기를 반환한다.
		@return MB 단위의 메모리 크기.
		*/
		UINT GetMemorySize() const;
		
		/**
		@brief 디스플레이 장치의 개수를 반환한다.
		*/
		UINT GetNumDisplays();

		/**
		@brief 비디오 어댑터의 인터페이스를 반환한다.
		@return CPDXGIAdapter 인터페이스
		*/
		const CPDXGIAdapter GetInterface() const;
		
		/**
		@brief 컨테이너 내의 디스플레이 장치를 반환한다.
		@param 디스플레이 장치의 인덱스
		@warning Out of index 동작시 크래시 발생.
		*/
		const MnDisplayDevice GetDisplayDevice(int index) const;

		/**
		@brief GPU가 지원하는 최대 피쳐 레벨을 반환한다.
		*/
		D3D_FEATURE_LEVEL GetMaxSupportedFeatureLevel() const;

	private:
		/**
		@brief DXGIAdapter 인터페이스로부터 최대 지원 피쳐레벨을 구한다.
		@return 정상적 동작시 S_OK 반환
		*/
		HRESULT _InitMaxSupportedFeatureLevel(CPDXGIAdapter cpAdapter);

	private:
		std::wstring		m_adapterName; ///< 비디오 어댑터의 이름
		UINT				m_videoMemorySize; ///< 비디오 어댑터의 비디오 메모리 크기
		CPDXGIAdapter		m_cpDXGIAdapter; ///< MnVideoAdapter가 참조하는 DXGI 인터페이스
		DXGI_ADAPTER_DESC	m_desc; ///< DXGIAdapter 인터페이스의 명세
		D3D_FEATURE_LEVEL	m_maxFeatureLevel; ///< 현재 비디오 어댑터의 최대 지원 피쳐 레벨
 		std::vector<MnDisplayDevice> m_displayDevices; ///< 초기화된 디스플레이 장치가 저장되는 컨테이너
	};
}
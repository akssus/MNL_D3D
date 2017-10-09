/**
@class MNL::MnD3DDevice
@author Akssus
@brief DIrectX11 디바이스와 디바이스 컨텍스트를 생성, 관리한다.
@section 개요
MnD3DDevice를 초기화 하기 위해선 초기화된 MnHardware 객체가 필요하다. \n
MnD3DDevice는 MnHardware 객체로부터 비디오 어댑터의 인터페이스를 얻어와 D3DDevice 인터페이스와 D3DDeviceContext 인터페이스를 생성한다. \n
초기화 된 MnD3DDevice는 MnRenderAPI 클래스에서 비디오 어댑터 장치와 상호작용 하는데 사용된다.
*/

#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"
#include "MnHardware.h"

namespace MNL
{
	class MnD3DDevice
	{
	public:
		MnD3DDevice();
		~MnD3DDevice();
		/**
		@brief D3DDevice, D3DDeviceContext 인터페이스를 생성, 초기화 한다.
		@param useDefaultAdapter 디폴트 비디오 어댑터 사용 여부.
		@return 초기화 성공 여부.
		@warning 현재 useDefaultAdapter 값과 관계 없이 디폴트 값으로 초기화 된다.
		*/
		HRESULT Init(const MnHardware& hardwareInfo, bool useDefaultAdapter);

		/**
		@brief D3DDevice 인터페이스를 반환한다.
		*/
		CPD3DDevice GetDevice() const;
		/**
		@brief D3DDeviceContext 인터페이스를 반환한다.
		*/
		CPD3DDeviceContext GetDeviceContext() const;

	private:
		CPD3DDevice m_cpD3DDevice; ///< D3Device 인터페이스
		CPD3DDeviceContext m_cpD3DDeviceContext; ///> D3DDeviceContext 인터페이스
	};
}
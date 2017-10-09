/**
@class MNL::MnDisplayDevice
@author Akssus
@brief 디스플레이 장치의 디스플레이 모드 정보를 얻어와 저장한다.

@section 개요
하나의 DisplayDevice는 하나의 디스플레이 장치(모니터)의 정보를 담고 있다.\n
지원하는 모든 해상도의 종류, 주사율 등의 정보를 제공하며 특정 해상도가 지원되는지 여부를 알 수 있다.\n
추가로 주어진 조건과 가장 가까운 지원되는 Display Mode를 찾아내는 GetClosestMode 메소드를 제공한다.\n
이 메소드가 필요한 이유는 이런 메소드가 없으면 사용자 혹은 개발자가 모니터가 지원하는 완벽하게 정확한 해상도와 주사율 값을 알아야 하기 때문에 불편하기 때문이다.\n
*/

#pragma once

#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <vector>
#include "MnTypedefs.h"

namespace MNL
{
	/**
	@brief 디스플레이 모드 정보를 담고있다.
	*/
	struct MnDisplayMode
	{
		UINT width, height;
		UINT numerator, denominator;
	};
	class MnDisplayDevice
	{
	public:
		MnDisplayDevice();
		~MnDisplayDevice();
		/**
		@brief DXGIOutput 인터페이스를 통해 모든 디스플레이 모드들을 얻어와 초기화 한다.
		@return 초기화 성공 여부.
		*/
		HRESULT Init(CPDXGIOutput cpOutput);


		/**
		@brief DXGIOutput 인터페이스를 반환한다.
		*/
		const CPDXGIOutput GetInterface() const;
		
		/**
		@brief 지원되는 디스플레이 모드 중 가장 흡사한 디스플레이 모드를 찾아 반환한다.
		@param width 해상도 넓이
		@param height 해상도 높이
		@param numerator 주사율의 분자
		@param denominator 주사율 분모
		*/
		MnDisplayMode GetClosestMode(UINT width, UINT height, UINT numerator, UINT denominator) const;


		/**
		@brief 해당 해상도를 지원하는지 여부를 반환한다.
		@return 지원할 경우 true 반환.
		*/
		bool IsSupportResolutionOf(UINT width, UINT height) const;

		/**
		현재 디스플레이 장치의 디스플레이 모드 개수를 반환한다.
		*/
		UINT GetNumDisplayModes() const;


	private:
		std::vector<DXGI_MODE_DESC> m_displayModeDescs; ///< 디스플레이 명세가 저장된 컨테이너
		std::vector<MnDisplayMode>  m_displayModes; ///< 디스플레이 모드가 저장된 컨테이너
		UINT						m_numDisplayModes; ///< 디스플레이 모드 개수
		CPDXGIOutput				m_cpDXGIOutput; ///< DXGIOutput 인터페이스
	};
}
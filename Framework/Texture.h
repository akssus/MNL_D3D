/**
@class MNL::Textrue
@brief 게임오브젝트가 가지는 텍스쳐 컴포넌트
@author Akssus
@section 개요
MN_TEXTURE_TYPE 열거형을 통해 텍스쳐 용도에 텍스쳐를 매핑한다.
*/

#pragma once
#include <map>
#include <memory>
#include "MnGameObjectComponent.h"
#include "Render/MnMeshTextureCombination.h"

namespace MNL
{
	enum MN_TEXTURE_TYPE
	{
		MN_TEXTURE_DIFFUSE,
		MN_TEXTURE_NORMAL_MAP,
	};
	class Texture : public MnGameObjectComponent
	{
	public:
		Texture();
		~Texture();

		void SetTexture(const std::shared_ptr<MnMeshTexture>& spTexture, MN_TEXTURE_TYPE textureType);

		/**
		@brief 해당 텍스쳐 타입의 텍스쳐를 반환한다.
		@return 텍스쳐가 존재하지 않을 경우 nullptr 반환
		*/
		std::shared_ptr<MnMeshTexture> GetTexture(MN_TEXTURE_TYPE textureType);

	private:
		std::map<MN_TEXTURE_TYPE,std::shared_ptr<MnMeshTexture>> m_tblTextures;
	};
}
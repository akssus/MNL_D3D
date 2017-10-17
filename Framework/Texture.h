/**
@class MNL::Textrue
@brief ���ӿ�����Ʈ�� ������ �ؽ��� ������Ʈ
@author Akssus
@section ����
MN_TEXTURE_TYPE �������� ���� �ؽ��� �뵵�� �ؽ��ĸ� �����Ѵ�.
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
		@brief �ش� �ؽ��� Ÿ���� �ؽ��ĸ� ��ȯ�Ѵ�.
		@return �ؽ��İ� �������� ���� ��� nullptr ��ȯ
		*/
		std::shared_ptr<MnMeshTexture> GetTexture(MN_TEXTURE_TYPE textureType);

	private:
		std::map<MN_TEXTURE_TYPE,std::shared_ptr<MnMeshTexture>> m_tblTextures;
	};
}
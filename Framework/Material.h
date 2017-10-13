#include "MnGameObjectComponent.h"
#include <memory>
#include "Render/MnMaterial.h"


#pragma once
namespace MNL
{
	class Material : public MnGameObjectComponent
	{
	public:
		Material();
		~Material();

		void SetMaterial(const std::shared_ptr<MnMaterial>& spMaterial);

		/**
		@return ���׸����� ���õ��� �ʾ��� ��� nullptr ��ȯ
		*/
		std::shared_ptr<MnMaterial> GetMaterial() const;

	private:
		std::shared_ptr<MnMaterial> m_spMaterial;
	};
}
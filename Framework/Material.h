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
		@return 머테리얼이 세팅되지 않았을 경우 nullptr 반환
		*/
		std::shared_ptr<MnMaterial> GetMaterial() const;

	private:
		std::shared_ptr<MnMaterial> m_spMaterial;
	};
}
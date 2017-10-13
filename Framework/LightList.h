#pragma once

#include "MnWorldComponent.h"
#include <vector>
#include <memory>
#include "Render/MnLightSource.h"

namespace MNL
{
	class LightList : public MnWorldComponent
	{
	public:
		LightList();
		~LightList();

		void AddLight(const std::shared_ptr<MnLightSource>& spLight);
		void RemoveLight(int index);
		void ClearLights();

		std::vector<std::shared_ptr<MnLightSource>>& GetLights();
		std::shared_ptr<MnLightSource>& GetLight(int index);

	private:
		std::vector<std::shared_ptr<MnLightSource>> m_lstLights;
	};
}
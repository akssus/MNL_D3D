#pragma once

#include "Render/MnCamera.h"
#include "MnWorldComponent.h"
#include <vector>
#include <memory>

namespace MNL
{
	class CameraList : public MnWorldComponent
	{
	public:
		CameraList();
		~CameraList();

		void AddCamera(const std::shared_ptr<MnCamera>& spCamera);
		void RemoveCamera(int index);
		void ClearCameras();

		std::vector<std::shared_ptr<MnCamera>>& GetCameras();
		std::shared_ptr<MnCamera>& GetCamera(int index);
		
	private:
		std::vector<std::shared_ptr<MnCamera>> m_lstCameras;
	};
}
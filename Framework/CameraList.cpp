#include "CameraList.h"

using namespace MNL;

CameraList::CameraList()
{
}


CameraList::~CameraList()
{
}


void CameraList::AddCamera(const std::shared_ptr<MnCamera>& spCamera)
{
	m_lstCameras.push_back(spCamera);
}
void CameraList::RemoveCamera(int index)
{
	assert(index >= 0 && index < m_lstCameras.size());
	m_lstCameras.erase(m_lstCameras.begin()+index);
}
void CameraList::ClearCameras()
{
	m_lstCameras.clear();
}

std::vector<std::shared_ptr<MnCamera>>& CameraList::GetCameras()
{
	return m_lstCameras;
}
std::shared_ptr<MnCamera>& CameraList::GetCamera(int index)
{
	assert(index >= 0 && index < m_lstCameras.size());
	return m_lstCameras[index];
}
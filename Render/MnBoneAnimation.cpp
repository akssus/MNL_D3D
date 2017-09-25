#include "MnBoneAnimation.h"

using namespace MNL;

MnBoneAnimation::MnBoneAnimation():m_totalDuration(0.0)
{

}
MnBoneAnimation::~MnBoneAnimation()
{

}
void MnBoneAnimation::SetName(const std::string& name)
{
	m_name = name;
}
const std::string& MnBoneAnimation::GetName() const
{
	return m_name;
}
void MnBoneAnimation::SetTotalDuration(double duration)
{
	m_totalDuration = duration;
}
double MnBoneAnimation::GetTotalDuration() const
{
	return m_totalDuration;
}
void MnBoneAnimation::AddElement(const MnBoneAnimationElement& keyFrame)
{
	m_lstElements.push_back(keyFrame);
}
UINT MnBoneAnimation::GetNumElements() const
{
	return m_lstElements.size();
}

MnBoneAnimationElement MnBoneAnimation::GetElement(UINT index) const
{
	return m_lstElements[index];
}
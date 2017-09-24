#pragma once
#include <d3d11.h>
#include <string>
#include <vector>
#include "MnBoneAnimationElement.h"

namespace MNL
{
	class MnBoneAnimation
	{
	public:
		MnBoneAnimation();
		~MnBoneAnimation();

		void SetName(const std::string& name);
		const std::string& GetName() const;

		void SetTotalDuration(double duration);
		double GetTotalDuration() const;

		void AddElement(const MnBoneAnimationElement& keyFrame);
		UINT GetNumElements() const;
		MnBoneAnimationElement GetElement(UINT index) const;

	private:
		std::string m_name;
		double m_totalDuration;
		std::vector<MnBoneAnimationElement> m_lstElements;

	};
}
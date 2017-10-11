#pragma once
#include "Renderer.h"
#include "Render/MnSkinnedMeshRenderer.h"


namespace MNL
{
	class SkinnedMeshRenderer : public Renderer
	{
	public:
		SkinnedMeshRenderer();
		~SkinnedMeshRenderer();

		virtual void Render();

	private:
		void _Init();

	private:
		bool m_isInitialized;
		MnSkinnedMeshRenderer m_renderer;

	};
}

#pragma once
#include "Renderer.h"

namespace MNL
{
	class StaticMeshRenderer : public Renderer
	{
	public:
		StaticMeshRenderer();
		~StaticMeshRenderer();

		virtual void Render();
	};
}
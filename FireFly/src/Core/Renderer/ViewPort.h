#pragma once

#include "Renderer.h"
#include "RendererAPI.h"
#include "Core/Events/WindowEvent.h"

namespace FireFly
{
	class ViewPort
	{
	public:
		virtual ~ViewPort() = default;
		static void OnEvent(WindowResizeEvent& e);
		static void SetIsLockRatio(bool isLockRatio);
		static void SetRatio(float ratio);
	private:
		static float s_Ratio;
		static bool s_IsLockRatio;
	};
}
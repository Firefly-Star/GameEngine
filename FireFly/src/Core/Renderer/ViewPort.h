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
		static void SetSize(unsigned int width, unsigned int height);
		inline static std::pair<unsigned int, unsigned int> GetSize() { return std::make_pair(s_Width, s_Height); }
	private:
		static float s_Ratio;
		static bool s_IsLockRatio;
		static unsigned int s_Width, s_Height;
	};
}
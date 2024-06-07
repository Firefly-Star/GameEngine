#pragma once

#include "Core/Controller/MouseController.h"

#include <GLFW/glfw3.h>

namespace FireFly
{
	class WindowsMouseController : public MouseController
	{
	public:
		WindowsMouseController(void* window);
		virtual void HideImpl() override;
		virtual void DisplayImpl() override;
		virtual void SetCursorPosImpl(float x, float y) override;
	private:
		GLFWwindow* m_Window;
	};
}
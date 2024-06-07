#include "ffpch.h"
#include "WindowsMouseController.h"


namespace FireFly
{
	WindowsMouseController::WindowsMouseController(void* window)
		:m_Window((GLFWwindow*)window)
	{
	}
	void WindowsMouseController::HideImpl()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	void WindowsMouseController::DisplayImpl()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	void WindowsMouseController::SetCursorPosImpl(float x, float y)
	{
		glfwSetCursorPos(m_Window, x, y);
	}
}

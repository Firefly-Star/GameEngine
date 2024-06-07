#include "ffpch.h"

#include <GLFW/glfw3.h>

#include "WindowsInput.h"

namespace FireFly
{
	bool WindowsInput::IsKeyPressed(int keycode) const
	{
		FF_CORE_ASSERT(m_Window, "Invalid Window!");
		GLFWwindow* window = (GLFWwindow*)m_Window;

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMousePressed(int button) const
	{
		FF_CORE_ASSERT(m_Window, "Invalid Window!");
		GLFWwindow* window = (GLFWwindow*)m_Window;

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePos() const
	{
		FF_CORE_ASSERT(m_Window, "Invalid Window!");
		GLFWwindow* window = (GLFWwindow*)m_Window;

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return { (float)x, (float)(h - y)};
	}
}
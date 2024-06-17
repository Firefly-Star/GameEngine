#pragma once

#include "Core/Input.h"
#include <GLFW/glfw3.h>


namespace FireFly
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput(void* window) : m_Window((GLFWwindow*)window) {}

		virtual bool IsKeyPressedImpl(int keycode) const override;
		virtual bool IsMousePressedImpl(int button) const override;
		virtual std::pair<float, float> GetMousePosImpl() const override;
	private:
		GLFWwindow* m_Window;
	};
}
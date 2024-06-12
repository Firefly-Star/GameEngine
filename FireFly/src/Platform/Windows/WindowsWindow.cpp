#include "ffpch.h"

#include <GLFW/glfw3.h>

#include "WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Core/Events/MouseEvent.h"

#include <glad/glad.h>
#include <imgui.h>

namespace FireFly
{
	bool WindowsWindow::s_IsGLFWInitialized = false;

	Window* Window::Create(const WindowProp& windowProp)
	{
		static Window* ptr = nullptr;
		if (!ptr)
		{
			ptr = new WindowsWindow(windowProp);
		}
		return ptr;
	}

	void Window::Terminate()
	{
		glfwTerminate();
	}

	WindowsWindow::WindowsWindow(const WindowProp& windowProp)
	{
		Init(windowProp);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProp& windowProp)
	{
		m_WindowData.prop.m_Height = windowProp.m_Height;
		m_WindowData.prop.m_Width = windowProp.m_Width;
		m_WindowData.prop.m_Tittle = windowProp.m_Tittle;

		FF_CORE_INFO("Creating a WindowsWindow \"{}\": {}* {}", m_WindowData.prop.m_Tittle, m_WindowData.prop.m_Width, m_WindowData.prop.m_Height);
		if (!s_IsGLFWInitialized)
		{
			glfwSetErrorCallback([](int error_code, const char* description)
				{
					FF_CORE_ERROR("GLFW error ({0}): {}!", error_code, description);
				});
			int status = glfwInit();
			FF_CORE_ASSERT(status, "Failed to initialize GLFW!");
			s_IsGLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(windowProp.m_Width, windowProp.m_Height, windowProp.m_Tittle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FF_CORE_ASSERT(status, "Failed to initialize GLAD!");

		glfwSetErrorCallback([](int errorType, const char* description) {
			FF_CORE_ERROR("GLFW Error[{}]: {}", errorType, description);
			});

		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVsync(true);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent e(key, 0);
						data.eventCallBack(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						data.eventCallBack(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent e(key, 1);
						data.eventCallBack(e);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent e(codepoint);
				data.eventCallBack(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mod)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MousePressedEvent e(button);
					data.eventCallBack(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent e(button);
					data.eventCallBack(e);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallBack(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent e((float)xPos, (float)yPos);
				data.eventCallBack(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.prop.m_Width = width;
				data.prop.m_Height = height;

				WindowResizeEvent e(width, height);
				data.eventCallBack(e);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent e;
				data.eventCallBack(e);
			});
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetEventCallback(const EventCallBackFunc& func)
	{
		m_WindowData.eventCallBack = func;
	}

	void WindowsWindow::SetVsync(bool enable)
	{
		if (enable)
		{
			glfwSwapInterval(1);
			m_WindowData.Vysnc = true;
		}
		else
		{
			glfwSwapInterval(0);
			m_WindowData.Vysnc = false;
		}
	}

}
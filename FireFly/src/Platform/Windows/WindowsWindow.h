#pragma once


#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Layer.h"
#include "WindowsInput.h"

struct GLFWwindow;

namespace FireFly
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProp& windowProp = WindowProp());
		~WindowsWindow();
		void Init(const WindowProp& windowProp = WindowProp());
		void OnUpdate();
		void Shutdown();
		inline unsigned int GetWidth() const override { return m_WindowData.prop.m_Width; }
		inline unsigned int GetHeight() const override { return m_WindowData.prop.m_Height; }
		void SetEventCallback(const EventCallBackFunc& func) override;
		void SetVsync(bool enabled) override;
		inline bool IsVsync() { return m_WindowData.Vysnc; }
		void* GetWindowHandle() override { return (void*)m_Window; }
	private:
		struct WindowData
		{
			WindowProp prop;
			bool Vysnc;
			EventCallBackFunc eventCallBack;
		};
		GLFWwindow* m_Window;
		WindowData m_WindowData;
		static bool s_IsGLFWInitialized;
	};


}
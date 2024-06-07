#pragma once

#include "Core.h"
#include "Events/Event.h"
namespace FireFly
{
	struct WindowProp
	{
		int m_Height;
		int m_Width;
		std::string m_Tittle;

		WindowProp(int width = 1280, int height = 720, std::string tittle = "FireFly Engine")
			: m_Height(height), m_Width(width), m_Tittle(tittle){}
	};

	class Window
	{
	public:
		using EventCallBackFunc = std::function<void(Event&)>;
		virtual ~Window(){}

		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallBackFunc& func) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVsync() = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProp& windowProp = WindowProp());

		static void Terminate();

	};
}
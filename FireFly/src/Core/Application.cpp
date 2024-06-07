#include "ffpch.h"

#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Log.h"

#include "TimeStep.h"
#include "Core/Controller/MouseController.h"

#include "Renderer/Renderer.h"
#include "Renderer/ViewPort.h"

#include <glad/glad.h>

namespace FireFly
{
	Application::Application()
	{
		WindowProp prop(1600, 960);
		ViewPort::SetRatio(16.0f / 9.0f);
		m_Window.reset(Window::Create(prop));
		m_Window->SetEventCallback(FF_BIND_EVENT_FN(Application::OnEvent));
		void* window_ptr = m_Window->GetWindowHandle();
		m_Input.reset(Input::Create(window_ptr));
		m_ImGuiLayer = std::make_shared<ImGuiLayer>("ImGui", window_ptr);
		m_ImGuiLayer->OnAttach();

		TimeStep::Init();
		MouseController::SetWindow(m_Window->GetWindowHandle());
		Renderer::Init();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			Renderer::Clear();
			
			m_LayerStack.OnUpdate(m_Input);
			
			m_ImGuiLayer->Begin();
			m_LayerStack.OnImGuiRender();
			m_ImGuiLayer->OnImGuiRender();
			m_ImGuiLayer->End();


			TimeStep::OnUpdate();

			Renderer::DrawIndexed(6);
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	bool Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.EventDispatch<WindowCloseEvent>(FF_BIND_EVENT_FN(Application::OnClose));
		dispatcher.EventDispatch<WindowResizeEvent>(FF_BIND_EVENT_FN(Application::OnWindowResize));
		bool isHandled = m_LayerStack.OnEvent(e);
		
		return isHandled;
	}

	bool Application::OnClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		ViewPort::OnEvent(e);
		return false;
	}
}
#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"


#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace FireFly 
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Ref<Layer> layer);
		void PushOverLayer(Ref<Layer> layer);
		inline const Ref<Window> GetWindow() { return m_Window; }
	private:
		bool OnEvent(Event& e);
		bool OnClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Ref<Window> m_Window;
		Ref<Input> m_Input;
		Ref<ImGuiLayer> m_ImGuiLayer;

		LayerStack m_LayerStack;

		bool m_Running = true;


		FireFly::Ref<FireFly::VertexBuffer> m_VB;
		FireFly::Ref<FireFly::IndexBuffer> m_IB;
		FireFly::Ref<FireFly::Shader> m_Shader;
		FireFly::Ref<FireFly::Texture> m_Texture;
		FireFly::Ref<FireFly::BufferLayout> m_Layout;
	};

	//To be defined in the CLIENT(Sandbox)
	Ref<Application> CreateApplication();

}
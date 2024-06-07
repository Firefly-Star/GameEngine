#pragma once

#include "Core/Core.h"
#include "Core/Layer.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Core/Input.h"

namespace FireFly
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const char* name, void* window);
		~ImGuiLayer();

		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0;
		void* m_Window;
	};
}
#pragma once

#include "Core/Core.h"
#include "Utils/ParamPacker.h"
namespace FireFly
{
	class Input
	{
	public:
		static Input* Create(void* window);
		Input(void* window): m_Window(window) {}
		virtual bool IsKeyPressed(int keycode) const = 0;
		virtual bool IsMousePressed(int button) const = 0;
		virtual std::pair<float, float> GetMousePos() const = 0;
	protected:
		void* m_Window;
	};
}
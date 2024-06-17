#pragma once

#include "Core/Core.h"
#include "Utils/ParamPacker.h"
namespace FireFly
{
	class Input
	{
	public:
		static void Init(void* window);
		static bool IsKeyPressed(int keycode);
		static bool IsMousePressed(int button);
		static std::pair<float, float> GetMousePos();
		virtual bool IsKeyPressedImpl(int keycode) const = 0;
		virtual bool IsMousePressedImpl(int button) const = 0;
		virtual std::pair<float, float> GetMousePosImpl() const = 0;
	protected:
		static Scope<Input> s_Instance;
	};
}
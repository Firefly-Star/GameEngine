#include "ffpch.h"

#include "Input.h"
#include "OS/OSAPI.h"
#include "Platform/Windows/WindowsInput.h"

namespace FireFly
{
	Scope<Input> Input::s_Instance = nullptr;
	void Input::Init(void* window)
	{
		switch (OSAPI::GetOSAPI())
		{
		case OSAPI::OS::Windows: s_Instance.reset(new WindowsInput(window)); return;
		default: FF_CORE_ASSERT(false, "Unknown OS!");
		}
	}
	bool Input::IsKeyPressed(int keycode)
	{
		return s_Instance->IsKeyPressedImpl(keycode);
	}
	bool Input::IsMousePressed(int button)
	{
		return s_Instance->IsMousePressedImpl(button);
	}
	std::pair<float, float> Input::GetMousePos()
	{
		return s_Instance->GetMousePosImpl();
	}
}
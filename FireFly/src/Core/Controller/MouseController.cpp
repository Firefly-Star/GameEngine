#include "ffpch.h"

#include "MouseController.h"
#include "Platform/Windows/WindowsMouseController.h"

namespace FireFly
{
	Scope<MouseController> MouseController::s_Instance = nullptr;

	void MouseController::SetWindow(void* window)
	{
		s_Instance.reset(new WindowsMouseController(window));
	}

	void MouseController::Hide()
	{
		s_Instance->HideImpl();
	}

	void MouseController::Display()
	{
		s_Instance->DisplayImpl();
	}

	void MouseController::SetCursorPos(float x, float y)
	{
		s_Instance->SetCursorPosImpl(x, y);
	}
}
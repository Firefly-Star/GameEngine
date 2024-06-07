#pragma once

namespace FireFly
{
	class MouseController
	{
	public:
		virtual ~MouseController() = default;
		static void SetWindow(void* window);
		static void Hide();
		static void Display();
		static void SetCursorPos(float x, float y);
	private:
		virtual void HideImpl() = 0;
		virtual void DisplayImpl() = 0;
		virtual void SetCursorPosImpl(float x, float y) = 0;
	private:
		static Scope<MouseController> s_Instance;
	};
}
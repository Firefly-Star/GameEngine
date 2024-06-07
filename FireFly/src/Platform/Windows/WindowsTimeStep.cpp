#include "ffpch.h"

#include "WindowsTimeStep.h"

#include <GLFW/glfw3.h>

namespace FireFly
{
	void WindowsTimeStep::InitImpl()
	{
		m_LastTime = 0.0f;
		m_DeltaTime = 1 / 60.0f;
	}
	void WindowsTimeStep::OnUpdateImpl()
	{
		float time = (float)glfwGetTime();
		m_DeltaTime = time - m_LastTime;
		m_LastTime = time;
	}
	float WindowsTimeStep::GetDeltaTimeImpl()
	{
		return m_DeltaTime;
	}
	float WindowsTimeStep::GetTimeImpl()
	{
		return m_LastTime;
	}
}
#include "ffpch.h"

#include "TimeStep.h"

#include "OS/OSAPI.h"
#include "Platform/Windows/WindowsTimeStep.h"

namespace FireFly
{
	Ref<TimeStep> TimeStep::s_Instance = std::make_shared<WindowsTimeStep>();

	void TimeStep::Init()
	{
		s_Instance->InitImpl();
	}

	void TimeStep::OnUpdate()
	{
		s_Instance->OnUpdateImpl();
	}
	float TimeStep::GetDeltaTime()
	{
		return s_Instance->GetDeltaTimeImpl();
	}
	float TimeStep::GetTime()
	{
		return s_Instance->GetDeltaTimeImpl();
	}
}
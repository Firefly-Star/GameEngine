#pragma once

#include "Core/TimeStep.h"

namespace FireFly
{
	class WindowsTimeStep : public TimeStep
	{
	public:
		WindowsTimeStep() = default;
		~WindowsTimeStep() = default;
		virtual void InitImpl() override;
		virtual void OnUpdateImpl() override;
		virtual float GetDeltaTimeImpl() override;
		virtual float GetTimeImpl() override;
	private:
		float m_LastTime;
		float m_DeltaTime;
	};
}
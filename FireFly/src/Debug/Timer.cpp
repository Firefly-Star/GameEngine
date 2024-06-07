#include "ffpch.h"

#include "Timer.h"

namespace FireFly
{
	PerformanceTimer::PerformanceTimer(const char* name)
		:m_Name(name)
	{
		m_BeginTime = std::chrono::high_resolution_clock::now();
	}

	PerformanceTimer::~PerformanceTimer()
	{
		auto endtime = std::chrono::high_resolution_clock::now();
		auto duration = endtime - m_BeginTime;
		FF_CORE_TRACE("{} ms", duration.count() * 0.001);
	}
}
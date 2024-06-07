#pragma once

#include <chrono>
namespace FireFly
{
	class PerformanceTimer
	{
	public:
		PerformanceTimer(const char* name);
		~PerformanceTimer();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_BeginTime;
		const char* m_Name;
	};
}
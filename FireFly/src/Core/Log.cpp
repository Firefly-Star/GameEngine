#include "ffpch.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "Log.h"

namespace FireFly
{
	std::shared_ptr<spdlog::logger> Log::s_Corelogger;
	std::shared_ptr<spdlog::logger> Log::s_Clientlogger;
	void Log::Init()
	{
		spdlog::set_pattern("%^[%Y/%m/%d %H:%M:%S]%n[%l]: %v%$");
		s_Corelogger = spdlog::stderr_color_mt("Engine");
		s_Clientlogger = spdlog::stderr_color_mt("App");

		s_Corelogger->set_level(spdlog::level::trace);
		s_Clientlogger->set_level(spdlog::level::trace);
	}
}
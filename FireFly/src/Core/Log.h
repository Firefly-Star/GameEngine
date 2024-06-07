#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "Core.h"


namespace FireFly
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCorelogger() { return s_Corelogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientlogger() { return s_Clientlogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Corelogger;
		static std::shared_ptr<spdlog::logger> s_Clientlogger;
	};
}



#define FF_CORE_TRACE(...)		::FireFly::Log::GetCorelogger()->trace(__VA_ARGS__)
#define FF_CORE_DEBUG(...)		::FireFly::Log::GetCorelogger()->debug(__VA_ARGS__)
#define FF_CORE_INFO(...)		::FireFly::Log::GetCorelogger()->info(__VA_ARGS__)
#define FF_CORE_WARN(...)		::FireFly::Log::GetCorelogger()->warn(__VA_ARGS__)
#define FF_CORE_ERROR(...)		::FireFly::Log::GetCorelogger()->error(__VA_ARGS__)
#define FF_CORE_CRITICAL(...)	::FireFly::Log::GetCorelogger()->critical(__VA_ARGS__)
								
#define FF_CLIENT_TRACE(...)	::FireFly::Log::GetClientlogger()->trace(__VA_ARGS__)
#define FF_CLIENT_DEBUG(...)	::FireFly::Log::GetClientlogger()->debug(__VA_ARGS__)
#define FF_CLIENT_INFO(...)		::FireFly::Log::GetClientlogger()->info(__VA_ARGS__)
#define FF_CLIENT_WARN(...)		::FireFly::Log::GetClientlogger()->warn(__VA_ARGS__)
#define FF_CLIENT_ERROR(...)	::FireFly::Log::GetClientlogger()->error(__VA_ARGS__)
#define FF_CLIENT_CRITICAL(...) ::FireFly::Log::GetClientlogger()->critical(__VA_ARGS__)

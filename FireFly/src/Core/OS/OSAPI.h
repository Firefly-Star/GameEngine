#pragma once

namespace FireFly
{
	class OSAPI
	{
	public:
		enum class OS
		{
			None = 0,
			Windows = 1//, Mac, Linux etc.
		};
		static OS GetOSAPI() { return s_OSAPI; }
	private:
		static OS s_OSAPI;
	};
}
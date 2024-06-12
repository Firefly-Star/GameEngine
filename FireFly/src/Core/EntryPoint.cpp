#include "ffpch.h"
#include "EntryPoint.h"

#include "Application.h"

int main(int argc, char** argv)
{
	FireFly::Log::Init();
	DEBUG_ONLY(FF_CORE_DEBUG("Configuration: Debug"););
	auto app = FireFly::CreateApplication();
	app->Run();
}

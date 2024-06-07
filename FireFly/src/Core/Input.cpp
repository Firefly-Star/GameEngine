#include "ffpch.h"

#include "Input.h"
#include "OS/OSAPI.h"
#include "Platform/Windows/WindowsInput.h"

namespace FireFly
{
	Input* Input::Create(void* window)
	{
		switch (OSAPI::GetOSAPI())
		{
		case(OSAPI::OS::Windows):return new WindowsInput(window);
		}
	}
}
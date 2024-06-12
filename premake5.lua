workspace "FireFly"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "FireFly/vendor/GLFW/src/glfw-3.4/include"
	IncludeDir["Glad"] = "FireFly/vendor/Glad/include"
	IncludeDir["ImGui"] = "FireFly/vendor/ImGui"
	IncludeDir["GLM"] = "FireFly/vendor/GLM/glm-master"
	IncludeDir["stb"] = "FireFly/vendor/stb_image"
	IncludeDir["assimp"] = "FireFly/vendor/assimp/include"

	include "FireFly/vendor/GLFW/src/glfw-3.4"
	include "FireFly/vendor/Glad"
	include "FireFly/vendor/ImGui"

--------------------------------------------------------------------------------

	project "FireFly"

		location "FireFly"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "On"

		targetdir ("bin/" .. outputdir .. "/%{ prj.name }")
		objdir ("bin-int/" .. outputdir .. "/%{ prj.name }")

		pchheader "ffpch.h"
		pchsource "%{prj.name}/src/ffpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/GLM/glm-master/glm/**.hpp",
			"%{prj.name}/vendor/GLM/glm-master/glm/**.inl",
			"%{prj.name}/vendor/stb_image/*.cpp",
			"%{prj.name}/vendor/stb_image/*.h",
			"%{prj.name}/vendor/assimp/include/assimp/**.h",
			"%{prj.name}/vendor/assimp/include/assimp/**.hpp"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.ImGui}/backends",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.stb}",
			"%{IncludeDir.assimp}"
		}

		links
		{
			"GLFW",
			"opengl32.lib",
			"Glad",
			"ImGui"
		}

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		
		filter "system:windows"
			systemversion "latest"
		
			defines
			{
				"FF_PLATFORM_WINDOWS",
				"FF_BUILD_DLL"
			}
		
		filter "configurations:Debug"
			defines "FF_DEBUG"
			symbols "On"
			optimize "Off"
			runtime "Debug"
			

		filter "configurations:Release"
			optimize "On"
			runtime "Release"

		filter "configurations:Debug"
			optimize "Full"
			runtime "Release"
------------------------------------------------------------------------

	project "Sandbox"

		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "On"

		targetdir ("bin/" .. outputdir .. "/%{ prj.name }	")
		objdir ("bin-int/" .. outputdir .. "/%{ prj.name }")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"FireFly/vendor/spdlog/include",
			"FireFly/src",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.ImGui}/backends",
			"%{IncludeDir.assimp}"
		}

		links
		{
			"FireFly",
		}

		filter "system:windows"
			systemversion "latest"

			defines
			{
				"FF_PLATFORM_WINDOWS",
			}

		filter "configurations:Debug"
			defines "FF_DEBUG"
			symbols "On"
			runtime "Debug"
			links
			{
				"FireFly/vendor/assimp/bin/Debug/assimp-vc143-mtd.lib"
			}

		filter "configurations:Release"
			optimize "On"
			runtime "Release"
			links
			{
				"FireFly/vendor/assimp/bin/Release/assimp-vc143-mt.lib"
			}

		filter "configurations:Debug"
			optimize "Full"
			runtime "Release"

----------------------------------------------------------------------------
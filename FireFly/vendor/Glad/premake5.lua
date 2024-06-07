project "Glad"
    language "C"
    kind "StaticLib"

    targetdir ("../../../bin/"..outputdir.."/%{prj.name}")
    objdir ("../../../bin-int/"..outputdir.."/%{prj.name}")

    includedirs
    {
        "include"
    }

    files
    {
        "**.*"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
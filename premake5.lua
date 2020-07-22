workspace "Kure"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Kure/vendor/GLFW/include"

--this includes the premake5 file in glfw
--eg copy and pasted into this premake5 file
include "Kure/vendor/GLFW"

project "Kure"
	location "Kure"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "krpch.h"
	pchsource "Kure/src/krpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"KR_PLATFORM_WINDOWS",
			"KR_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations.Debug"
		defines "KR_DEBUG"
		symbols "On"

	filter "configurations.Debug"
		defines "KR_RELEASE"
		optimize "On"

	filter "configurations.Debug"
		defines "KR_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Kure/vendor/spdlog/include",
		"Kure/src"
	}

	links
	{
		"Kure"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"KR_PLATFORM_WINDOWS"
		}


	filter "configurations.Debug"
		defines "KR_DEBUG"
		symbols "On"

	filter "configurations.Debug"
		defines "KR_RELEASE"
		optimize "On"

	filter "configurations.Debug"
		defines "KR_DIST"
		optimize "On"

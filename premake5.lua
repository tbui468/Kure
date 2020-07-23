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
IncludeDir["glad"] = "Kure/vendor/glad/include"
IncludeDir["ImGui"] = "Kure/vendor/ImGui"

--this includes the premake5 file in glfw
--essentially copy and pasted into this premake5 file
include "Kure/vendor/GLFW"
include "Kure/vendor/glad"
include "Kure/vendor/ImGui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}"
	}

	--these are projects we link
	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"KR_PLATFORM_WINDOWS",
			"KR_BUILD_DLL",
			"GLFW_INCLUDE_NONE" --will not include opengl headers when including glfw
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations.Debug"
		defines 
		{
			"KR_DEBUG",
			"KR_ENABLE_ASSERTS"
		}
--		buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations.Debug"
		defines "KR_RELEASE"
--		buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations.Debug"
		defines "KR_DIST"
--		buildoptions "/MD"
		runtime "Release"
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
		defines 
		{
			"KR_DEBUG",
			"KR_ENABLE_ASSERTS"
		}
--		buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations.Debug"
		defines "KR_RELEASE"
--		buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations.Debug"
		defines "KR_DIST"
--		buildoptions "/MD"
		runtime "Release"
		optimize "On"

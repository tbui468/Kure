workspace "Kure"
	architecture "x64"
	startproject "Kure-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	defines "_CRT_SECURE_NO_WARNINGS"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Kure/vendor/GLFW/include"
IncludeDir["glad"] = "Kure/vendor/glad/include"
IncludeDir["ImGui"] = "Kure/vendor/ImGui"
IncludeDir["glm"] = "Kure/vendor/glm"
IncludeDir["stb"] = "Kure/vendor/stb"

--this includes the premake5 file in that directory
--essentially copy and pasted into this premake5 file
include "Kure/vendor/GLFW"
include "Kure/vendor/glad"
include "Kure/vendor/ImGui"


project "Kure"
	location "Kure"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "krpch.h"
	pchsource "Kure/src/krpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
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
		systemversion "latest"

		defines
		{
			"KR_PLATFORM_WINDOWS",
			"KR_BUILD_DLL",
			"GLFW_INCLUDE_NONE" --will not include opengl headers when including glfw
		}



	filter "configurations:Debug"
		defines "KR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Kure/vendor/spdlog/include",
		"Kure/src",
		"%{IncludeDir.glm}",
		"Kure/vendor"
	}

	links
	{
		"Kure"
	}

	filter "system:windows"
		systemversion "latest"



	filter "configurations:Debug"
		defines "KR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KR_DIST"
		runtime "Release"
		optimize "on"





project "Kure-Editor"
	location "Kure-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Kure/vendor/spdlog/include",
		"Kure/src",
		"%{IncludeDir.glm}",
		"Kure/vendor"
	}

	links
	{
		"Kure"
	}

	filter "system:windows"
		systemversion "latest"



	filter "configurations:Debug"
		defines "KR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KR_DIST"
		runtime "Release"
		optimize "on"

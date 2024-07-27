project "CherryTree"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ctpch.h"
	pchsource "src/CherryTree/ctpch.cpp"

	files
	{
		"src/CherryTree/**.h",
		"src/CherryTree/**.hpp",
		"src/CherryTree/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",

		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"src/CherryTree",

		"%{Dependencies.spdlog.IncludeDir}",
		"%{Dependencies.glfw.IncludeDir}",
		"%{Dependencies.Pulse.IncludeDir}"
	}

	links
	{
		"%{Dependencies.glfw.LibName}",
		"%{Dependencies.Pulse.LibName}"
	}

	filter "system:windows"
		defines "CT_PLATFORM_WINDOWS"
		systemversion "latest"
		staticruntime "on"

	filter "system:linux"
		defines "CT_PLATFORM_LINUX"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		defines "CT_CONFIG_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "CT_CONFIG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CT_CONFIG_DIST"
		runtime "Release"
		optimize "Full"
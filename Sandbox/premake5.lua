project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	architecture "x86_64"
	
	-- debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}") 
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"%{wks.location}/vendor",

		"%{wks.location}/CherryTree/src",

		"%{Dependencies.spdlog.IncludeDir}",
		"%{Dependencies.glfw.IncludeDir}",
		"%{Dependencies.Pulse.IncludeDir}"
	}

	links
	{
		"CherryTree"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",

		"GLFW_INCLUDE_NONE"
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
		optimize "on"
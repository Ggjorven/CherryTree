project "Glad"
	kind "StaticLib"
	language "C"

    architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
    {
        "src/glad.c"
    }

    includedirs
    {
        "src",
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "On"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        runtime "Release"
        optimize "Full"
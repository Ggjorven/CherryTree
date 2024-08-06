------------------------------------------------------------------------------
-- Dependencies
------------------------------------------------------------------------------
VULKAN_SDK = os.getenv("VULKAN_SDK")

Dependencies = 
{
	-- Vulkan Related
	Vulkan = 
	{
		Windows = 
		{
			LibName = "vulkan-1",
			IncludeDir = "%{VULKAN_SDK}/Include/",
			LibDir = "%{VULKAN_SDK}/Lib/"
		},
		Linux =  
		{
			LibName = "vulkan",
			IncludeDir = "%{VULKAN_SDK}/include/",
			LibDir = "%{VULKAN_SDK}/lib/"
		}
	},
	ShaderC = 
	{
		LibName = "shaderc_shared"
	},
	VMA = 
	{
		LibName = "VMA",
		IncludeDir = "%{wks.location}/vendor/vma/include"
	},

	-- All other Third-Party libraries
	spdlog = 
	{
		IncludeDir = "%{wks.location}/vendor/spdlog/include"
	},
	glfw = 
	{
		LibName = "GLFW",
		IncludeDir = "%{wks.location}/vendor/glfw/include"
	},
	glad = 
	{
		LibName = "Glad",
		IncludeDir = "%{wks.location}/vendor/glad/include"
	},
	glm = 
	{
		IncludeDir = "%{wks.location}/vendor/glm"
	},
	Pulse = 
	{
		LibName = "Pulse",
		IncludeDir = "%{wks.location}/vendor/Pulse/Pulse/src"
	}
}
------------------------------------------------------------------------------

------------------------------------------------------------------------------
-- Solution
------------------------------------------------------------------------------
outputdir = "%{cfg.buildcfg}-%{cfg.system}"

workspace "CherryTree"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

group "Dependencies"
	include "vendor/glfw"
	include "vendor/glad"
	include "vendor/Pulse/Pulse"
	include "vendor/vma"
group ""

group "Main"
	include "CherryTree"
group ""

include "Sandbox"
------------------------------------------------------------------------------
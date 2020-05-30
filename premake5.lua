workspace "JLHE"
	architecture "x64"

	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "JLHE/vendor/GLFW/include"

group "Dependencies"
	include "JLHE/vendor/GLFW"
group ""

project "JLHE"
	location "JLHE"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jlhepch.h"
	pchsource "JLHE/src/jlhepch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links {
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"JLHE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JLHE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JHLE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JLHE_DIST"
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
    
		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs {
			"JLHE/src",
			"JLHE/vendor",
			"JLHE/vendor/spdlog/include"
		}

		links {
			"JLHE"
		}

	filter "system:windows"
		systemversion "latest"
		defines {
			"JLHE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JLHE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JLHE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JLHE_DIST"
		runtime "Release"
		optimize "on"

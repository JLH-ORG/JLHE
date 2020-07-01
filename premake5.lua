workspace "JLHE"
	architecture "x64"

	startproject "JLHE-Editor"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "JLHE/vendor/GLFW/include"
IncludeDir["Glad"] = "JLHE/vendor/Glad/include"
IncludeDir["ImGui"] = "JLHE/vendor/imgui"
IncludeDir["glm"] = "JLHE/vendor/glm"
IncludeDir["stb_image"] = "JLHE/vendor/stb_image"

group "Dependencies"
	include "JLHE/vendor/GLFW"
	include "JLHE/vendor/Glad"
	include "JLHE/vendor/imgui"
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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/glm/glm/**.hpp",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",		
		"%{IncludeDir.stb_image}"
	}
	
	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"JLHE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
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
			"JLHE/vendor/spdlog/include",
			"JLHE/vendor",
			"%{IncludeDir.glm}"
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


project "JLHE-Editor"
	location "JLHE-Editor"
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
			"JLHE/vendor/spdlog/include",
			"JLHE/vendor",
			"%{IncludeDir.glm}"
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

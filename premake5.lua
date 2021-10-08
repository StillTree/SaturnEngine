workspace "SaturnEngine"
	architecture "x64"
    startproject "AppSandbox"

	configurations
	{
		"Debug",
		"Release"
	}

project "SaturnEngine"
	location "SaturnEngine"
	kind "SharedLib"
	language "C++"

	targetdir "bin/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}_%{prj.name}"
	objdir "obj/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}_%{prj.name}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/libs/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines "_WINDLL"

		postbuildcommands "{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}_AppSandbox"

	filter "configurations:Debug"
		defines "_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"

project "AppSandbox"
	location "AppSandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir "bin/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}_%{prj.name}"
	objdir "obj/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}_%{prj.name}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"SaturnEngine/libs/spdlog/include",
		"SaturnEngine/src"
	}

	links
	{
		"SaturnEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
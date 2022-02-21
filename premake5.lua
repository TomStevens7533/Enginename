workspace "MiniGin"
	architecture "x64"
	startproject "MiniGin"

	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories

IncludeDir = {}
IncludeDir["Glad"] = "3rdParty/Glad/include"
IncludeDir["SDL2"] = "3rdParty/SDL2/include"
IncludeDir["SDL2_image"] = "3rdParty/SDL2_image/include"
IncludeDir["SDL2_ttf"] = "3rdParty/SDL2_ttf/include"
IncludeDir["glm"] = "3rdParty/glm"
IncludeDir["vld"] = "3rdParty/VLD"


include "3rdParty/Glad"


project "MiniGin"
	location "Minigin"
	kind "ConsoleApp"
	cppdialect "C++20"
	language"C++"
	staticruntime "On"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	toolset ("v143")

	flags {
		"FatalWarnings"  --Treat warnings as errors
	}

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"$(SolutionDir)3rdParty/VLD/**.h",
		"$(SolutionDir)3rdParty/glm/**.hpp",
		"$(SolutionDir)3rdParty/glm/**.inl"
		
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{
		"$(SolutionDir)3rdParty/glm",
		"$(SolutionDir)3rdParty/SDL2/include",
		"$(SolutionDir)3rdParty/SDL2_image/include",
		"$(SolutionDir)3rdParty/SDL2_ttf/include",
		"$(SolutionDir)3rdParty/Glad",
		"$(SolutionDir)3rdParty/VLD/include"
		
	}
	libdirs 
	{
		"$(SolutionDir)3rdParty/SDL2/lib/x64",
		"$(SolutionDir)3rdParty/SDL2/lib/x64",
		"$(SolutionDir)3rdParty/SDL2_image/lib/x64",
		"$(SolutionDir)3rdParty/SDL2_ttf/lib/x64",
		"$(SolutionDir)3rdParty/VLD"
	}
	links
	{
		"Glad",
		"opengl32.lib",
		"xinput.lib",
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib",
		"vld.lib",
		
		
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"


	
	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "On"


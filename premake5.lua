workspace "MiniGin"
	startproject "MiniGin"
    toolset ("v143")


configurations { "Debug", "Release" }
platforms { "Win64" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories

IncludeDir = {}
IncludeDir["Glad"] = "3rdParty/Glad/include"
IncludeDir["GLFW"] = "3rdParty/GLFW/include"
IncludeDir["SDL2"] = "3rdParty/SDL2/include"
IncludeDir["imgui"] = "3rdParty/imgui"
IncludeDir["SDL2_image"] = "3rdParty/SDL2_image/include"
IncludeDir["SDL2_ttf"] = "3rdParty/SDL2_ttf/include"
IncludeDir["glm"] = "3rdParty/glm"
IncludeDir["vld"] = "3rdParty/VLD"

include "3rdParty/GLFW"
include "3rdParty/Glad"
include "3rdParty/imgui"



project "MiniGin"
	location "Minigin"
	kind "ConsoleApp"
	cppdialect "C++20"
	language"C++"
	staticruntime "On"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
 toolset ("v143")
	warnings "High"


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
		"$(SolutionDir)3rdParty/GLFW/include",
		"$(SolutionDir)3rdParty/imgui",
		"$(SolutionDir)3rdParty/SDL2_ttf/include",
		"$(SolutionDir)3rdParty/Glad/include",
		"$(SolutionDir)3rdParty/VLD/include"
		
	}
	libdirs 
	{
		"$(SolutionDir)3rdParty/SDL2/lib/$(Platform)",
		"$(SolutionDir)3rdParty/SDL2/lib/$(Platform)",
		"$(SolutionDir)3rdParty/SDL2_image/lib/$(Platform)",
		"$(SolutionDir)3rdParty/SDL2_ttf/lib/$(Platform)",
		"$(SolutionDir)3rdParty/VLD/lib/$(Platform)"
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
		"GLFW",
		"imgui"
		
		
	}

	postbuildcommands {
		"{COPY} $(SolutionDir)3rdParty/SDL2/lib/$(Platform)/SDL2.dll %{cfg.targetdir}",
		"{COPY} $(SolutionDir)3rdParty/SDL2_image/lib/$(Platform)/*.dll %{cfg.targetdir}",
		"{COPY} $(SolutionDir)3rdParty/SDL2_ttf/lib/$(Platform)/*.dll %{cfg.targetdir}",


	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"


	filter "configurations:Debug*"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release*"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "On"

			


	


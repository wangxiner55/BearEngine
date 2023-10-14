workspace "Bear"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Bear"
    location "Bear"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"



        defines
        {
            "BR_BUILD_DLL",
            "BR_PLATFORM_WINDOWS"
        }


        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Hive")
        }


    filter "configurations:Debug"
        defines "BR_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "BR_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "BR_DIST"
        optimize "On"



project "Hive"
    location "Hive"
    kind "ConsoleAPP"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Bear/vendor/spdlog/include",
        "Bear/src"
    }

    links
    {
        "Bear"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.22000.0"



        defines
        {
            "BR_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "BR_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "BR_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "BR_DIST"
        optimize "On"

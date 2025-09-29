workspace "TextureConverter"

    architecture "x86_64"
    configurations { "Debug", "Release" }

    defines { "_WINDOWS" }

    startproject "TextureConverter"

project "TextureConverter"
    kind "ConsoleApp"
    language "C++"
    targetdir "../generated/output/%{cfg.buildcfg}/"
    objdir "../generated/obj/%{cfg.buildcfg}/TextureConverter/"
    
    -- デバッグ時の作業ディレクトリを指定
    debugdir "%{wks.location}"
    files { "**.h", "**.cpp"}

    warnings "Extra"
    buildoptions { "/utf-8", "/MP" }

    includedirs {
        "$(SolutionDir).",
    }

    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"
        runtime "Debug"
        staticruntime "On"
    
    filter "configurations:Release"
        defines { "NDEBUG", "_NDEBUG" ,"RELEASE","_RELEASE" }
        optimize "Full"
        runtime "Release"
        staticruntime "On"



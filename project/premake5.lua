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
    removefiles  { "externals/**"}

    warnings "Extra"
    buildoptions { "/utf-8", "/MP" }

    includedirs {
        "$(SolutionDir).",
        "$(SolutionDir)code",
        "$(SolutionDir)externals",
        "$(SolutionDir)externals/DirectXTex",
    }

    links { "DirectXTex" }

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

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        postbuildcommands {
            "copy \"$(WindowsSdkDir)bin\\$(TargetPlatformVersion)\\x64\\dxcompiler.dll\" \"$(TargetDir)dxcompiler.dll\"",
            "copy \"$(WindowsSdkDir)bin\\$(TargetPlatformVersion)\\x64\\dxil.dll\" \"$(TargetDir)dxil.dll\""
    }

project "DirectXTex"
    kind "StaticLib"
    language "C++"

    location "externals/DirectXTex/"
    targetdir "../generated/output/%{cfg.buildcfg}/"
    objdir "../generated/obj/%{cfg.buildcfg}/DirectXTex/"
    targetname "DirectXTex"
    files { "externals/DirectXTex/**.h", "externals/DirectXTex/**.cpp" }
    includedirs { "$(ProjectDir)","$(ProjectDir)Shaders/Compiled" }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
    filter "configurations:Debug"
        runtime "Debug"       -- Debug ランタイム (MTd) を使用
        symbols "On"
        staticruntime "On"
    filter "configurations:Release"
         runtime "Release"     -- Release ランタイム (MT) を使用
         optimize "Full"
         staticruntime "On"

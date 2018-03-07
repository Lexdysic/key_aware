solution "KeyGraph"
    configurations { "Debug", "Release" }
    location("../.build/projects/" .. _ACTION)
    platforms { "x64" }
    debugdir ".."

    project "KeyGraph"
        targetname "KeyGraph"
        language "C++"
        kind "ConsoleApp"

        flags { "StaticRuntime" }

        files {
            "../include/**",
            "../src/**",
            "../scripts/**.lua",
        }

        configuration { "Release" }
            flags { "Optimize" }
        configuration { "linux" }
            targetdir "../.build/bin/linux"
        configuration { "windows" }
            targetdir "../.build/bin/windows"
        configuration {}
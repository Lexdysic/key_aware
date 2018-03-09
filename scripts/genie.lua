kRootDir = ".."

solution "key_aware"
    configurations { "Debug", "Release" }
    platforms { "x32", "x64" }

    location(path.join(kRootDir, ".build", "projects", _ACTION))
    language "C++"
    
    
    -- flags
    flags {
        "StaticRuntime",
        "ExtraWarnings"
    }
    configuration { "Release" }
        flags {
            "Optimize"
        }
    configuration {}

    -- buildoptions
    configuration { "vs*" }
        buildoptions {
            "/std:c++17",
            "/permissive-"
        }
    configuration { "gmake" }
        buildoptions {
            "-std=c++17"
        }
    configuration {}

    -- targetdir
    configuration { "linux" }
        targetdir(path.join(kRootDir, ".build", "bin", "linux"))
    configuration { "windows" }
        targetdir(path.join(kRootDir, ".build", "bin", "windows"))
    configuration {}
    
    -- WindowsSDK
    configuration { "vs2017"}
        windowstargetplatformversion string.gsub(os.getenv("WindowsSDKVersion") or "10.0.10240.0", "\\", "")
    configuration {}

    project "key_aware"
        kind "StaticLib"
        
        includedirs {
            path.join(kRootDir, "include"),
        }

        files {
            path.join(kRootDir, "include", "**"),
            path.join(kRootDir, "src", "**"),
            path.join(kRootDir, "scripts", "**"),
        }



    project "key_aware_test"
        targetname "key_aware_test"
        debugdir ".."
        kind "ConsoleApp"

        ncludedirs {
            path.join(kRootDir, "include"),
        }

        files {
            path.join(kRootDir, "test", "**"),
        }

        links {
            "key_aware",
        }
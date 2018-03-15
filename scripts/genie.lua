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
    configuration { "Debug"}
        flags {
            "Symbols"
        }
    configuration {}

    -- buildoptions
    configuration { "vs*" }
        buildoptions {
            --"/std:c++17",
            "/permissive-"
        }
    configuration { "gmake" }
        buildoptions {
            --"-std=c++17"
        }
    configuration {}

	targetdir (path.join(kRootDir, ".build", ACTION, "bin"))
	objdir (path.join(kRootDir, ".build", _ACTION, "obj"))

    
    -- WindowsSDK
    configuration { "vs2017"}
        windowstargetplatformversion(string.gsub(os.getenv("WindowsSDKVersion") or "10.0.16299.0", "\\", ""))
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

    startproject "key_aware_sample"

    project "key_aware_sample"
        targetname "key_aware_sample"
        debugdir(path.join(kRootDir, "sample", "data"))
        kind "ConsoleApp"

        includedirs {
            path.join(kRootDir, "include"),
        }
        
        configuration { "linux" }
            libdirs(path.join(kRootDir, ".build", "bin", "linux"))
        configuration { "windows" }
            libdirs(path.join(kRootDir, ".build", "bin", "windows"))

        files {
            path.join(kRootDir, "sample", "src", "**"),
        }

        links {
            "key_aware",
        }

    project "key_aware_test"
        targetname "key_aware_test"
        debugdir(path.join(kRootDir, "test", "data"))
        kind "ConsoleApp"

        includedirs {
            path.join(kRootDir, "include"),
            path.join(kRootDir, "third_party"),
        }
        
        configuration { "linux" }
            libdirs(path.join(kRootDir, ".build", "bin", "linux"))
        configuration { "windows" }
            libdirs(path.join(kRootDir, ".build", "bin", "windows"))

        files {
            path.join(kRootDir, "test", "src", "**"),
        }

        links {
            "key_aware",
        }
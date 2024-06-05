workspace("Phoenix")
configurations({ "Debug", "Release" })
architecture("x86_64")
targetdir("bin/")
objdir("obj/")

project("Phoenix")
language("C++")
kind("ConsoleApp")

files({
	"src/**.cpp",
	"src/**.c",
	"src/**.h",
})

includedirs({
	"vendor/include",
	"include/",
})

libdirs({
	"./vendor/lib",
})

links({
	"glfw3",
	"lua",
})

filter("system:linux")
defines({ "PLATFORM_LINUX" })

filter("configurations:Debug")
optimize("Off")

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")

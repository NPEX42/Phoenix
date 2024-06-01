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

links({
	"glfw3",
})

filter("system:linux")
defines({ "PLATFORM_LINUX" })


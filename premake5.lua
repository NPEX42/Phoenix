workspace("Phoenix")
configurations({ "Debug", "Release" })
architecture("x86_64")
targetdir("bin/")
objdir("obj/")

project("Phoenix")
language("C++")
cppdialect("C++2a")
kind("StaticLib")

defines({"GLFW_INCLUDE_NONE"})

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
	"yaml-cpp",
	"nfd",
	"freetype",
	"png16",
	"z",
	"fmt",
})

filter("system:linux")
	defines({ "PNHX_LINUX" })
	links({
		"gtk-3",
		"gdk-3",
		"pangocairo-1.0",
		"pango-1.0",
		"harfbuzz",
		"atk-1.0",
		"cairo-gobject",
		"cairo",
		"gdk_pixbuf-2.0",
		"gobject-2.0",
		"glib-2.0",
		"dl",
		"m"
	})

filter("system:windows")
	defines({ "PNHX_WINDOWS" })
	links({
		"ole32",
		"shell32",
		"uuid"
	})


filter("system:linux")
defines({ "PLATFORM_LINUX" })

filter("configurations:Debug")
defines({"DEBUG"})
optimize("Off")
symbols "On"

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")
symbols "Off"


project("Sandbox")
language("C++")
cppdialect("C++2a")
kind("ConsoleApp")

files({
	"Sandbox/src/**.cpp",
	"Sandbox/src/**.c",
	"Sandbox/src/**.h",
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
	"yaml-cpp",
	"nfd",
	"fmt",
	"freetype",
	"png16",
	"z",
	"Phoenix",
})
-- -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 
-- -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

filter("system:linux")
	defines({ "PNHX_LINUX" })
	links({
		"gtk-3",
		"gdk-3",
		"pangocairo-1.0",
		"pango-1.0",
		"harfbuzz",
		"atk-1.0",
		"cairo-gobject",
		"cairo",
		"gdk_pixbuf-2.0",
		"gobject-2.0",
		"glib-2.0",
	})

filter("system:windows")
	defines({ "PNHX_WINDOWS" })
	links({
		"ole32",
		"shell32",
		"uuid"
	})

filter("configurations:Debug")
optimize("Off")
symbols "On"

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")
symbols "Off"

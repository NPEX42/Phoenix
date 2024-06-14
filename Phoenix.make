# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

RESCOMP = windres
TARGETDIR = bin
TARGET = $(TARGETDIR)/libPhoenix.a
INCLUDES += -Ivendor/include -Iinclude
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS += -lglfw3 -llua -lyaml-cpp -lnfd -lfreetype -lpng16 -lz -lfmt -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgobject-2.0 -lglib-2.0 -ldl -lm
LDDEPS +=
LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug)
OBJDIR = obj/Debug/Phoenix
DEFINES += -DPNHX_LINUX -DPLATFORM_LINUX -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O0 -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O0 -g -std=c++20
ALL_LDFLAGS += $(LDFLAGS) -Lvendor/lib -L/usr/lib64 -m64

else ifeq ($(config),release)
OBJDIR = obj/Release/Phoenix
DEFINES += -DPNHX_LINUX -DPLATFORM_LINUX -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=c++20
ALL_LDFLAGS += $(LDFLAGS) -Lvendor/lib -L/usr/lib64 -m64 -s

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Application2D.o
GENERATED += $(OBJDIR)/AssetManager.o
GENERATED += $(OBJDIR)/Buffer.o
GENERATED += $(OBJDIR)/Log.o
GENERATED += $(OBJDIR)/OGL.o
GENERATED += $(OBJDIR)/Phoenix.o
GENERATED += $(OBJDIR)/Renderer2D.o
GENERATED += $(OBJDIR)/Script.o
GENERATED += $(OBJDIR)/Shader.o
GENERATED += $(OBJDIR)/Texture.o
GENERATED += $(OBJDIR)/TextureAtlas.o
GENERATED += $(OBJDIR)/Toml.o
GENERATED += $(OBJDIR)/Util.o
GENERATED += $(OBJDIR)/glad.o
GENERATED += $(OBJDIR)/imgui.o
GENERATED += $(OBJDIR)/imgui_demo.o
GENERATED += $(OBJDIR)/imgui_draw.o
GENERATED += $(OBJDIR)/imgui_freetype.o
GENERATED += $(OBJDIR)/imgui_impl_glfw.o
GENERATED += $(OBJDIR)/imgui_impl_opengl3.o
GENERATED += $(OBJDIR)/imgui_tables.o
GENERATED += $(OBJDIR)/imgui_widgets.o
GENERATED += $(OBJDIR)/stb_image.o
GENERATED += $(OBJDIR)/ui.o
OBJECTS += $(OBJDIR)/Application2D.o
OBJECTS += $(OBJDIR)/AssetManager.o
OBJECTS += $(OBJDIR)/Buffer.o
OBJECTS += $(OBJDIR)/Log.o
OBJECTS += $(OBJDIR)/OGL.o
OBJECTS += $(OBJDIR)/Phoenix.o
OBJECTS += $(OBJDIR)/Renderer2D.o
OBJECTS += $(OBJDIR)/Script.o
OBJECTS += $(OBJDIR)/Shader.o
OBJECTS += $(OBJDIR)/Texture.o
OBJECTS += $(OBJDIR)/TextureAtlas.o
OBJECTS += $(OBJDIR)/Toml.o
OBJECTS += $(OBJDIR)/Util.o
OBJECTS += $(OBJDIR)/glad.o
OBJECTS += $(OBJDIR)/imgui.o
OBJECTS += $(OBJDIR)/imgui_demo.o
OBJECTS += $(OBJDIR)/imgui_draw.o
OBJECTS += $(OBJDIR)/imgui_freetype.o
OBJECTS += $(OBJDIR)/imgui_impl_glfw.o
OBJECTS += $(OBJDIR)/imgui_impl_opengl3.o
OBJECTS += $(OBJDIR)/imgui_tables.o
OBJECTS += $(OBJDIR)/imgui_widgets.o
OBJECTS += $(OBJDIR)/stb_image.o
OBJECTS += $(OBJDIR)/ui.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking Phoenix
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning Phoenix
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/Application2D.o: src/Application2D.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/AssetManager.o: src/AssetManager.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui.o: src/ImGui/imgui.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_demo.o: src/ImGui/imgui_demo.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_draw.o: src/ImGui/imgui_draw.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_freetype.o: src/ImGui/imgui_freetype.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_impl_glfw.o: src/ImGui/imgui_impl_glfw.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_impl_opengl3.o: src/ImGui/imgui_impl_opengl3.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_tables.o: src/ImGui/imgui_tables.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_widgets.o: src/ImGui/imgui_widgets.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Log.o: src/Log.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Phoenix.o: src/Phoenix.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Toml.o: src/Toml.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Util.o: src/Util.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Renderer2D.o: src/gfx/Renderer2D.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Shader.o: src/gfx/Shader.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Texture.o: src/gfx/Texture.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TextureAtlas.o: src/gfx/TextureAtlas.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Buffer.o: src/gfx/ogl/Buffer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/OGL.o: src/gfx/ogl/OGL.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/stb_image.o: src/gfx/stb_image.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ui.o: src/gfx/ui.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/glad.o: src/glad.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Script.o: src/scripting/Script.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif
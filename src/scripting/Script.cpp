
#include "Phoenix/AssetManager.hpp"
#include "Phoenix/Log.hpp"
#include "Phoenix/gfx/Renderer2D.hpp"
extern "C" {
    #include "lua/lua.h"
}
#include <Phoenix/scripting/Script.hpp>
#include <Phoenix/scripting/CAPI.hpp>
#include <memory>
#include <string>

namespace phnx {
    std::shared_ptr<Script> Script::LoadFile(const std::string& filepath) {
        lua_State* state = luaL_newstate();
        luaL_dofile(state, filepath.c_str());

        lua_register(state, "DrawSprite", DrawSprite);
        lua_register(state, "DrawRotatedSprite", DrawRotatedSprite);

        

        return std::make_shared<Script>(state);
    }

    void Script::SetupLibs() {
        luaL_openlibs(L);
    }

    Script::Script(lua_State* state) : L(state) {}

    bool Script::PushFunc(const std::string& func) {
        lua_getglobal(L, func.c_str());
        return (lua_isfunction(L, -1));
    }

    bool Script::TryCall(int argc, int retc) {
        lua_call(L, argc, retc);
        return true;
    }

    void Script::PushInt(int value) {
        lua_pushinteger(L, value);
    }
    void Script::PushBool(bool value) {
        lua_pushboolean(L, value);
    } 
    void Script::PushFloat(float value) {
        lua_pushnumber(L, value);
    }
    void Script::PushString(const std::string& str) {
        lua_pushstring(L, str.c_str());
    }

    void Script::CleanStack(int count) {
        lua_pop(L, count);
    }

    bool Script::SimpleCall(const std::string& func) {
        if (PushFunc(func)) {
            TryCall();
            CleanStack();
            return true;
        }
        return false;
    }

    bool Script::PushTable(const std::string& name) {
        lua_getglobal(L, name.c_str());
        return lua_istable(L, -1);
    }

    SpriteScript::SpriteScript(const std::string& filepath) {
        mScript = Script::LoadFile(filepath);
        mScript->SetupLibs();
    }

    void SpriteScript::Init() {
        mScript->SimpleCall("Init");
    }

    void SpriteScript::Render() {
        mScript->SimpleCall("Render");
    }

    void SpriteScript::Update() {
        mScript->SimpleCall("Update");
    }

    template<>
    int Script::GetField<int>(const std::string& field) {
        lua_pushstring(L, field.c_str());
        lua_gettable(L, -2);
        int value = (int) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return value;
    }

    template<>
    float Script::GetField<float>(const std::string& field) {
        lua_pushstring(L, field.c_str());
        lua_gettable(L, -2);
        int value = (int) lua_tonumber(L, -1);
        lua_pop(L, 1);
        return value;
    }

    template<>
    const char* Script::GetField<const char*>(const std::string& field) {
        lua_pushstring(L, field.c_str());
        lua_gettable(L, -2);
        const char* value = (const char*) lua_tostring(L, -1);
        lua_pop(L, 1);
        return value;
    }

}

int DrawSprite(lua_State *L) {
    float x, y, w, h;
    const char* spriteName;
    
    x = lua_tonumber(L, 1);
    y = lua_tonumber(L, 2);
    w = lua_tonumber(L, 3);
    h = lua_tonumber(L, 4);

    spriteName = lua_tostring(L, 5);

    phnx::gfx::SetAlbedo(phnx::AssetManager::GetTextureByName(spriteName));
    phnx::gfx::Quad({x, y}, {w, h});


    return 0;
}

int DrawRotatedSprite(lua_State* L) {
    float x, y, w, h, angle;
    const char* spriteName;
    
    x = lua_tonumber(L, 1);
    y = lua_tonumber(L, 2);
    w = lua_tonumber(L, 3);
    h = lua_tonumber(L, 4);
    angle = lua_tonumber(L, 5);

    spriteName = lua_tostring(L, 6);

    phnx::gfx::SetAlbedo(phnx::AssetManager::GetTextureByName(spriteName));
    phnx::gfx::RotatedQuad({x, y}, angle, {w, h});


    return 0;
}
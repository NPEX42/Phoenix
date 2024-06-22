
extern "C" {
    #include "lua/lua.h"

    // DrawSprite(x, y, w, h, sprite)
    int DrawSprite(lua_State* L);
    int DrawRotatedSprite(lua_State* L);
}
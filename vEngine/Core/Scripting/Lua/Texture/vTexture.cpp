#include "Core/Scripting/Lua/Texture/vTexture.h"

using namespace wi::graphics;

namespace wi::lua
{
    const char Texture::className[] = "texture";
    Luna<Texture>::FunctionType Texture::methods[] = {
	    { NULL, NULL }
    };
    Luna<Texture>::PropertyType Texture::properties[] = {
	    { NULL, NULL }
    }
    void Texture::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            Luna<Texture>::Register(L, "vEngine");
            initialized = true;
        }
    }
}

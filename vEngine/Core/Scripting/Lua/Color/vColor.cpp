#include "Core/Scripting/Lua/Color/vColor.h"

#include <string>

namespace wi::lua
{
    // Class Binder
    const char Color::className[] = "color";
    Luna<Color>::FunctionType Color::methods[] = {
        lunamethod(Color, getR),
        lunamethod(Color, getG),
        lunamethod(Color, getB),
        lunamethod(Color, getA),
        lunamethod(Color, setR),
        lunamethod(Color, setG),
        lunamethod(Color, setB),
        lunamethod(Color, setA),
        { NULL, NULL }
    };
    Luna<Color>::PropertyType Color::properties[] = {
        { NULL, NULL }
    };
    Color::Color(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 4)
        {
            this->color = wi::Color(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2), wi::lua::SGetInt(L, 3), wi::lua::SGetInt(L, 4));
        }
    }

    // Instance Binder
    void Color::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            Luna<Color>::Register(L, "vEngine");
        }
    }

    // Library Methods
    int Color::getR(lua_State* L)
    {
        wi::lua::SSetInt(L, this->color.getR());
        return 1;
    }
    int Color::getG(lua_State* L)
    {
        wi::lua::SSetInt(L, this->color.getG());
        return 1;
    }
    int Color::getB(lua_State* L)
    {
        wi::lua::SSetInt(L, this->color.getB());
        return 1;
    }
    int Color::getA(lua_State* L)
    {
        wi::lua::SSetInt(L, this->color.getA());
        return 1;
    }
    int Color::setR(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 4)
        {
            this->color.setR(wi::lua::SGetInt(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: color:setR(int red)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Color::setG(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 4)
        {
            this->color.setG(wi::lua::SGetInt(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: color:setG(int green)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Color::setB(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 4)
        {
            this->color.setB(wi::lua::SGetInt(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: color:setB(int blue)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Color::setA(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 4)
        {
            this->color.setA(wi::lua::SGetInt(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: color:setA(int alpha)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
}
#include "Core/Scripting/Lua/Backlog/vBacklog.h"
#include "Core/Tools/wiBacklog.h"

#include <string>

namespace wi::lua
{
    // Class Binder
    const char Backlog::className[] = "backlog";
    Luna<Backlog>::FunctionType Backlog::methods[] = {
        lunamethod(Backlog, clear),
        lunamethod(Backlog, post),
        lunamethod(Backlog, isActive),
        lunamethod(Backlog, setLevel),
        { NULL, NULL }
    };
    Luna<Backlog>::PropertyType Backlog::properties[] = {
        { NULL, NULL }
    };
    void Backlog::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            Luna<Backlog>::Register(L, "vEngine");
            wi::lua::RunText(L, "vEngine.backlog = vEngine.backlog();");
        }
    };

    // Class Methods
    int Backlog::clear(lua_State* L)
    {
        wi::backlog::clear();
        wi::lua::SSetBool(L, true);
        return 1;
    };

    int Backlog::post(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc <= 2)
        {
            wi::lua::SError(L, "Syntax: vEngine.backlog.post(string message, int level)!");
            wi::lua::SSetBool(L, false);
            return 0;
        }
        wi::backlog::post(wi::lua::SGetString(L, 1), wi::lua::SGetString(L, 2));
        wi::lua::SSetBool(L, true);
        return 1;
    };

    int Backlog::isActive(lua_State* L)
    {
        wi::lua::SSetBool(L, wi::backlog::isActive());
        return 1;
    };

    int Backlog::setLevel(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc <= 1)
        {
            wi::lua::SError(L, "Syntax: vEngine.backlog.setLevel(int level)");
            wi::lua::SSetBool(L, false);
            return 0;
        }
        wi::backlog::SetLogLevel((wi::backlog::LogLevel)wi::lua::SGetInt(L, 1));
        wi::lua::SSetBool(L, true);
        return 1;
    };
}
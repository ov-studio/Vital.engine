#include "vCompiler.h"

#include <string>

std::string moduleName = "Lua";
wi::vector<moduleDef> modules = {
    {
        "Shared",
        {
            "init.lua",
            "math.lua",
            "color.lua"
        }
    },
    {
        "Client",
        {
            "thread.lua"
        }
    },
    {
        "Server",
        {}
    }
};

int main()
{
    return sandbox::compiler::module::CompileModule(moduleName, modules);
}

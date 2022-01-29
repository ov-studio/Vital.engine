#include "vCompiler.h"

#include <string>

std::string moduleName = "Lua";
wi::vector<sandbox::compiler::module::moduleDef> modules = {
    {
        "Shared",
        {
            "index.lua",
            "math.lua"
        }
    },
    {
        "Client",
        {
            "thread.lua",
            "color.lua"
        }
    },
    {
        "Server",
        {
            "index.lua"
        }
    }
};

int main()
{
    return sandbox::compiler::module::CompileModule(moduleName, modules);
}

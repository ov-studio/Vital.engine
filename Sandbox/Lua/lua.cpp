#include "../compiler.h"

#include <string>

std::string moduleName = "Lua";
wi::vector<moduleDef> modules = {
    {
        "Shared",
        {}
    },
    {
        "Client",
        {
			"init.lua"
		}
    },
    {
        "Server",
        {}
    }
};

int main()
{
    return compileSandboxModule(moduleName, modules);
}

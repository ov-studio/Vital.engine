#pragma once
#include "../../vEngine.h"

#include <string>

namespace sandbox
{
    namespace compiler
    {
        struct moduleDef
        {
            std::string moduleName;
            wi::vector<std::string> moduleScripts;
        };
        int CompileModule(std::string moduleName, wi::vector<moduleDef> modules);
    };
};
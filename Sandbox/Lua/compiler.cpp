#include "../../vEngine/vEngine.h"

#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>

std::mutex locker;
std::string moduleName = "Lua";
std::string modulePath = moduleName;
struct moduleTypes
{
	std::string moduleName;
	wi::vector<std::string> moduleScripts;
};
wi::vector<moduleTypes> SandboxModule = {
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
	std::cout << "[Sandbox Compiler] Compiling " + moduleName + " module" << std::endl;

	wi::jobsystem::Initialize();
	wi::jobsystem::context ctx;
	modulePath += "/";
	wi::helper::MakePathAbsolute(modulePath);
	wi::Timer timer;

    std::string bundlerData = R"(
    #include "Core/Helpers/wiVector.h"
    namespace SandboxLua {    
        struct moduleTypes
        {
            std::string moduleName;
            wi::vector<std::string> moduleScripts;
        };
        wi::vector<moduleTypes> modules = {};
    )";

	for (int i = 0; i < SandboxModule.size(); ++i)
    {
        bundlerData = bundlerData + "modules.push({" + "\"" + SandboxModule[i].moduleName + "\"" + ", {";
		for (int j = 0; j < SandboxModule[i].moduleScripts.size(); ++j)
		{
            std::string scriptPath = SandboxModule[i].moduleScripts[j];
            wi::vector<uint8_t> fileData;
            if (wi::helper::FileRead(modulePath + SandboxModule[i].moduleName + "/" + scriptPath, fileData))
            {
                wi::jobsystem::Execute(ctx, [&bundlerData, scriptPath, fileData](wi::jobsystem::JobArgs args) {
                    locker.lock();
                    std::string scriptData = std::string(fileData.begin(), fileData.end());
                    bundlerData += "R\"(" + scriptData + ")\",";
                    std::cout << "Script Compiled: " << scriptPath << std::endl;
                    locker.unlock();
                });
            }
            else
            {
                locker.lock();
                std::cerr << "Script Compilation Failed: " << scriptPath << std::endl;
                locker.unlock();
                std::exit(1);
            }
            wi::jobsystem::Wait(ctx);
		}
        wi::jobsystem::Wait(ctx);
        bundlerData += "}});";
    }
	wi::jobsystem::Wait(ctx);
    bundlerData += "\n};\n";

    timer.record();
    wi::helper::FileWrite("wiSandbox" + moduleName + ".h", (uint8_t*)bundlerData.c_str(), bundlerData.length());
	std::cout << "[Sandbox Compiler] Finished compiling " + moduleName + " module in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
	return 0;
}

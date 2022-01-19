#include "vCompiler.h"

#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>

std::mutex locker;

int sandbox::compiler::CompileModule(std::string moduleName, wi::vector<moduleDef> modules)
{
    std::string moduleIdentifier = moduleName;
    std::string modulePath = "../../Sandbox/" + moduleName + "/";
    std::transform(moduleIdentifier.begin(), moduleIdentifier.end(), moduleIdentifier.begin(), ::tolower);
    std::cout << "[Sandbox Compiler] Compiling " + moduleName + " module" << std::endl;

    wi::jobsystem::Initialize();
    wi::jobsystem::context ctx;
    wi::helper::MakePathAbsolute(modulePath);
    wi::Timer timer;

    std::string bundlerData = "#include \"Core/Helpers/wiVector.h\"\n";
    bundlerData += "#include <string>\nnamespace sandbox {}\n";
    bundlerData += "namespace sandbox::" + moduleIdentifier + " {\n";
    bundlerData += "struct moduleDef\n{\n    std::string moduleName;\n    wi::vector<std::string> moduleScripts;\n};\n\nwi::vector<moduleDef> modules = {";
    for (int i = 0; i < modules.size(); ++i)
    {
        bundlerData = bundlerData + "\n{\n" + "\"" + modules[i].moduleName + "\"" + ",\n{";
        for (int j = 0; j < modules[i].moduleScripts.size(); ++j)
        {
            std::string scriptPath = modules[i].moduleScripts[j];
            wi::vector<uint8_t> fileData;
            if (wi::helper::FileRead(modulePath + modules[i].moduleName + "/" + scriptPath, fileData))
            {
                wi::jobsystem::Execute(ctx, [&bundlerData, scriptPath, fileData](wi::jobsystem::JobArgs args) {
                    locker.lock();
                    std::string scriptData = std::string(fileData.begin(), fileData.end());
                    bundlerData += "\nR\"(\n" + scriptData + "\n)\",";
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
        bundlerData += "\n}\n},";
    }
    wi::jobsystem::Wait(ctx);
    bundlerData += "\n};\n};\n";

    timer.record();
    wi::helper::FileWrite("../Core/Sandbox/.build/vSandbox" + moduleName + ".h", (uint8_t*)bundlerData.c_str(), bundlerData.length());
    std::cout << "[Sandbox Compiler] Finished compiling " + moduleName + " module in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
    return 0;
}

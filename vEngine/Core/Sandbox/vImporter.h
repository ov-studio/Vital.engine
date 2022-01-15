#pragma once
#include <string>

namespace sandbox
{
    namespace importer
    {
        namespace gltf
        {
            void LoadModel(const std::string& fileName, wi::scene::Scene& scene);
        };
    };
};
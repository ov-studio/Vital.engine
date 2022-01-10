#pragma once
#include <string>

namespace wi::scene
{
	struct Scene;
}

// TODO: PUT UNDER NAMESPACE SOON
void importSandboxModel_GLTF(const std::string& fileName, wi::scene::Scene& scene);


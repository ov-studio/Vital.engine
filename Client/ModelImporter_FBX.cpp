#include "stdafx.h"
#include "Core/Systems/wiScene.h"
#include "ModelImporter.h"

#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>

#include <string>
#include <istream>
#include <streambuf>

using namespace wi::graphics;
using namespace wi::scene;
using namespace wi::ecs;

bool importMesh(Scene& scene, Entity& rootEntity, FbxNode* pNode) {
	auto pMesh = pNode->GetMesh();
	if (!pMesh->IsTriangleMesh()) {
		printf("Non triangle meshes.\n");
		return false;
	}

	const FbxGeometryElementNormal* pNormals = pMesh->GetElementNormal(0);
	if (!pNormals) {
		pMesh->GenerateNormals();
		pNormals = pMesh->GetElementNormal(0);
	}
	const FbxGeometryElementUV* pUVs = pMesh->GetElementUV(0);

    const char* nodeName = pNode->GetName();
	Entity objectEntity = scene.Entity_CreateObject(nodeName);
	scene.Component_Attach(objectEntity, rootEntity);

	Entity meshEntity = scene.Entity_CreateMesh(nodeName);
	ObjectComponent& object = *scene.objects.GetComponent(objectEntity);
	MeshComponent& mesh = *scene.meshes.GetComponent(meshEntity);
	object.meshID = meshEntity;

	//wi::unordered_map<int, int> registered_materialIndices = {};
	uint32_t numTriangles = uint32_t(pMesh->GetPolygonCount());
	wi::unordered_map<size_t, uint32_t> uniqueVertices = {};

	for (uint32_t t = 0; t < numTriangles; t++) {
		//uint32_t triIndices[3];
		for (uint32_t v = 0; v < 3; v++) {
			int iPoint = pMesh->GetPolygonVertex(t, v);
			FbxVector4 point = pMesh->GetControlPointAt(iPoint);
			//FbxVector4 normal = GetVertexElement(pNormals, iPoint, t, v, FbxVector4(0, 0, 0, 0));
			//FbxVector2 uv = GetVertexElement(pUVs, iPoint, t, v, FbxVector2(0, 1));

			XMFLOAT3 pos = XMFLOAT3(
				float(point[0]),
				float(point[1]),
				float(point[2])
			);
            /*
			XMFLOAT3 nor = XMFLOAT3(
                float(normal[0]),
                float(normal[1]),
                float(normal[2]) 
            );
			XMFLOAT2 tex = XMFLOAT2(float(uv[0]), float(uv[1]));
            */

			XMFLOAT3 nor = XMFLOAT3(0, 0, 0);
			XMFLOAT2 tex = XMFLOAT2(0, 0);
			// eliminate duplicate vertices by means of hashing:
			size_t vertexHash = 0;
			//wi::helper::hash_combine(vertexHash, v);
			//wi::helper::hash_combine(vertexHash, v);
			//wi::helper::hash_combine(vertexHash, v);
			//wi::helper::hash_combine(vertexHash, materialIndex);

			uniqueVertices[vertexHash] = (uint32_t)mesh.vertex_positions.size();
			mesh.vertex_positions.push_back(pos);
			mesh.vertex_normals.push_back(nor);
			mesh.vertex_uvset_0.push_back(tex);
            mesh.indices.push_back(uniqueVertices[vertexHash]); // SOMETHNG IS WRONG HERE IMO
            mesh.subsets.back().indexCount++;
		}
	}
	mesh.CreateRenderData(); // CAUSES CRASHES
	return true;
}

bool importNode(Scene& scene, Entity& rootEntity, FbxNode* pNode) {
	if (auto pLight = pNode->GetLight()) {
		//if (!importLight(pNode, pLight))
			//return false;
	}
	else if (auto pMesh = pNode->GetMesh()) {
		if (!importMesh(scene, rootEntity, pNode))
			return false;
	}
	for (int i = 0, e = pNode->GetChildCount(); i < e; i++) {
		if (!importNode(scene, rootEntity, pNode->GetChild(i))) {
			return false;
		}
	}
	return true;
}

void ImportModel_FBX(const std::string& fileName, Scene& scene)
{
	std::string directory = wi::helper::GetDirectoryFromPath(fileName);
	std::string name = wi::helper::GetFileNameFromPath(fileName);
	std::string error;

	wi::vector<uint8_t> filedata;
	bool success = wi::helper::FileRead(fileName, filedata);

	if (success)
	{
		FbxManager* lSdkManager = FbxManager::Create();
		FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

        // Create an importer.
        FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
        // Initialize the importer.
		const char* lFilename = fileName.c_str();
        success = lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings());

        if (!success) {
            wi::backlog::post("Call to FbxImporter::Initialize() failed.\n", wi::backlog::LogLevel::Error);
            wi::backlog::post(lImporter->GetStatus().GetErrorString(), wi::backlog::LogLevel::Error);
        }
		else {
			ios->SetBoolProp(IMP_FBX_MATERIAL, true);
			ios->SetBoolProp(IMP_FBX_TEXTURE, true);
			ios->SetBoolProp(IMP_FBX_LINK, true);
			ios->SetBoolProp(IMP_FBX_SHAPE, true);
			ios->SetBoolProp(IMP_FBX_GOBO, true);
			ios->SetBoolProp(IMP_FBX_ANIMATION, false);
			ios->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);

			// Create a new scene so it can be populated by the imported file.
			FbxScene* lScene = FbxScene::Create(lSdkManager, lFilename);
			// Import the contents of the file into the scene.
			if (lImporter->Import(lScene))
			{
				//if (lScene->GetGlobalSettings().GetSystemUnit() != FbxSystemUnit::m)
					//FbxSystemUnit::m.ConvertScene(lScene);

				// triangulate
				FbxGeometryConverter GeometryConverter(lSdkManager);
				GeometryConverter.Triangulate(lScene, true, false);
				FbxNode* root = lScene->GetRootNode();
				if (!root) return;
                        
                Entity rootEntity = CreateEntity();
                scene.transforms.Create(rootEntity);
                scene.names.Create(rootEntity) = name;
    
				if (!importNode(scene, rootEntity, root)) return;
			}
		}
	}
	else
	{
		error = "Failed to read file: " + fileName;
	}

	if (!error.empty())
	{
		wi::backlog::post(error, wi::backlog::LogLevel::Error);
	}
}

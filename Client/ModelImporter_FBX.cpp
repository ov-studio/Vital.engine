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

/*
typedef std::unordered_map<std::string, uint32_t> TextureLookupType;
struct ImportState {
	ImportState(model_import::Model& _model) : model(_model) {}

	model_import::Model& model;
	TextureLookupType textureLookup;
};

bool importNode(ImportState& state, FbxNode* pNode);
bool importMesh(ImportState& state, FbxNode* pNode);
bool importMaterial(ImportState& state, model_import::Mesh& mesh, FbxSurfaceMaterial* pFbxMaterial);
bool importLight(ImportState& state, FbxNode* pNode, FbxLight* pLight);
uint32_t importTexture(ImportState& state, FbxFileTexture* pFileTexture, bool sRGB);
*/


struct LoaderState
{
	Scene* scene;
	wi::unordered_map<int, Entity> entityMap;  // node -> entity
};


bool importMesh(LoaderState& state, FbxNode* pNode) {
	auto pMesh = pNode->GetMesh();
	if (!pMesh->IsTriangleMesh()) {
		printf("error: We only support triangle meshes.\n");
		return false;
	}

	/*
	model_import::Mesh mesh;
	mesh.transform = AsTransform(pNode->EvaluateGlobalTransform()) * GetGeometryTransform(pNode);

	// Import the materials.
	int materialCount = pNode->GetMaterialCount();
	for (int n = 0; n < materialCount; n++) {
		FbxSurfaceMaterial* material = pNode->GetMaterial(n);
		if (!importMaterial(state, mesh, material)) {
			return false;
		}
	}

	const FbxGeometryElementNormal* pNormals = pMesh->GetElementNormal(0);
	if (!pNormals) {
		// Generate normals if we don't have any
		pMesh->GenerateNormals();
		pNormals = pMesh->GetElementNormal(0);
	}

	const FbxGeometryElementUV* pUVs = pMesh->GetElementUV(0);

	const FbxLayerElementMaterial* pPolygonMaterials = pMesh->GetElementMaterial();
	assert(pPolygonMaterials != nullptr);
	assert(pPolygonMaterials->GetReferenceMode() == FbxGeometryElement::eIndex ||
		pPolygonMaterials->GetReferenceMode() == FbxGeometryElement::eIndexToDirect);
	FbxGeometryElement::EMappingMode mappingMode = pPolygonMaterials->GetMappingMode();
	auto getMaterialIndex = [pPolygonMaterials, mappingMode, materialCount](uint32_t triangleIndex) {
		int lookupIndex = 0;
		switch (mappingMode) {
		case FbxGeometryElement::eByPolygon:
			lookupIndex = triangleIndex;
			break;
		case FbxGeometryElement::eAllSame:
			lookupIndex = 0;
			break;
		default:
			assert(false);
			break;
		}

		int materialIndex = pPolygonMaterials->mIndexArray->GetAt(lookupIndex);
		assert(materialIndex >= 0 && materialIndex < materialCount);
		return uint32_t(materialIndex);
	};

	// vertex deduplication
	UnorderedMapGenerator<hvvr::ShadingVertex, uint32_t>::Type hashMap;
	*/

	uint32_t numTriangles = uint32_t(pMesh->GetPolygonCount());
	//mesh.data.verts.reserve(numTriangles * 3);
	//mesh.data.triShade.resize(numTriangles);

	//Entity rootEntity = CreateEntity();
	//state->scene.transforms.Create(rootEntity);
	//state.scene.names.Create(rootEntity) = name;

	//Entity meshEntity = scene.Entity_CreateMesh(x.name);
	//MeshComponent& mesh = *scene.meshes.GetComponent(meshEntity);

	for (uint32_t t = 0; t < numTriangles; t++) {
		uint32_t triIndices[3];
		for (uint32_t v = 0; v < 3; v++) {
			int iPoint = pMesh->GetPolygonVertex(t, v);

			/*
			FbxVector4 point = pMesh->GetControlPointAt(iPoint);
			FbxVector4 normal = GetVertexElement(pNormals, iPoint, t, v, FbxVector4(0, 0, 0, 0));
			FbxVector2 uv = GetVertexElement(pUVs, iPoint, t, v, FbxVector2(0, 1));

			hvvr::ShadingVertex vertex = {};
			vertex.pos = hvvr::vector3(float(point[0]), float(point[1]), float(point[2]));
			vertex.normal = hvvr::vector4h(hvvr::vector4(float(normal[0]), float(normal[1]), float(normal[2]), 0));
			vertex.uv = hvvr::vector2(float(uv[0]), 1.0f - float(uv[1]));

			auto it = hashMap.find(vertex);
			if (it != hashMap.end()) {
				// it's a duplicate vertex
				triIndices[v] = it->second;
			}
			else {
				// we haven't run into this vertex yet
				uint32_t index = uint32_t(mesh.data.verts.size());
				mesh.data.verts.emplace_back(vertex);
				hashMap[vertex] = index;
				triIndices[v] = index;
			}
			*/
		}

		/*
		uint32_t materialIndex = getMaterialIndex(t);

		hvvr::PrecomputedTriangleShade& triShade = mesh.data.triShade[t];
		triShade.indices[0] = triIndices[0];
		triShade.indices[1] = triIndices[1];
		triShade.indices[2] = triIndices[2];
		triShade.material = materialIndex;
		*/
	}

	//hvvr::GenerateTopology(mesh.data);

	//state.model.meshes.emplace_back(std::move(mesh));
	return true;
}

bool importNode(LoaderState& state, FbxNode* pNode) {
	//auto& node = state.gltfModel.nodes[nodeIndex];
	//Scene& scene = *state.scene;
	//Entity entity = INVALID_ENTITY;
	if (auto pLight = pNode->GetLight()) {
		//if (!importLight(pNode, pLight))
			//return false;
	}
	else if (auto pMesh = pNode->GetMesh()) {
		if (!importMesh(state, pNode))
			return false;
	}

	for (int i = 0, e = pNode->GetChildCount(); i < e; i++) {
		if (!importNode(state, pNode->GetChild(i))) {
			return false;
		}
		wi::backlog::post("wow node loop worked perfectly!\n");
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

				LoaderState state;
				state.scene = &scene;

				FbxNode* root = lScene->GetRootNode();
				if (!root) {
					return;
				}
				if (!importNode(state, root))
					return;
				wi::backlog::post("Tron: Loaded into importer!.\n");
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

	if (success)
	{
		/*
		Entity rootEntity = CreateEntity();
		scene.transforms.Create(rootEntity);
		scene.names.Create(rootEntity) = name;
		// Load material library:
		wi::vector<Entity> materialLibrary = {};
		for (auto& obj_material : obj_materials)
		{
			Entity materialEntity = scene.Entity_CreateMaterial(obj_material.name);
			MaterialComponent& material = *scene.materials.GetComponent(materialEntity);

			material.baseColor = XMFLOAT4(obj_material.diffuse[0], obj_material.diffuse[1], obj_material.diffuse[2], 1);
			material.textures[MaterialComponent::BASECOLORMAP].name = obj_material.diffuse_texname;
			material.textures[MaterialComponent::DISPLACEMENTMAP].name = obj_material.displacement_texname;
			material.emissiveColor.x = obj_material.emission[0];
			material.emissiveColor.y = obj_material.emission[1];
			material.emissiveColor.z = obj_material.emission[2];
			material.emissiveColor.w = std::max(obj_material.emission[0], std::max(obj_material.emission[1], obj_material.emission[2]));
			//material.refractionIndex = obj_material.ior;
			material.metalness = obj_material.metallic;
			material.textures[MaterialComponent::NORMALMAP].name = obj_material.normal_texname;
			material.textures[MaterialComponent::SURFACEMAP].name = obj_material.specular_texname;
			material.roughness = obj_material.roughness;

			if (material.textures[MaterialComponent::NORMALMAP].name.empty())
			{
				material.textures[MaterialComponent::NORMALMAP].name = obj_material.bump_texname;
			}
			if (material.textures[MaterialComponent::SURFACEMAP].name.empty())
			{
				material.textures[MaterialComponent::SURFACEMAP].name = obj_material.specular_highlight_texname;
			}

			for (auto& x : material.textures)
			{
				if (!x.name.empty())
				{
					x.name = directory + x.name;
				}
			}

			material.CreateRenderData();

			materialLibrary.push_back(materialEntity); // for subset-indexing...
		}

		if (materialLibrary.empty())
		{
			// Create default material if nothing was found:
			Entity materialEntity = scene.Entity_CreateMaterial("OBJImport_defaultMaterial");
			MaterialComponent& material = *scene.materials.GetComponent(materialEntity);
			materialLibrary.push_back(materialEntity); // for subset-indexing...
		}

		// Load objects, meshes:
		for (auto& shape : obj_shapes)
		{
			Entity objectEntity = scene.Entity_CreateObject(shape.name);
			scene.Component_Attach(objectEntity, rootEntity);
			Entity meshEntity = scene.Entity_CreateMesh(shape.name + "_mesh");
			ObjectComponent& object = *scene.objects.GetComponent(objectEntity);
			MeshComponent& mesh = *scene.meshes.GetComponent(meshEntity);

			object.meshID = meshEntity;

			wi::unordered_map<int, int> registered_materialIndices = {};
			wi::unordered_map<size_t, uint32_t> uniqueVertices = {};

			for (size_t i = 0; i < shape.mesh.indices.size(); i += 3)
			{
				tinyobj::index_t reordered_indices[] = {
					shape.mesh.indices[i + 0],
					shape.mesh.indices[i + 1],
					shape.mesh.indices[i + 2],
				};

				// todo: option param would be better
				bool flipCulling = false;
				if (flipCulling)
				{
					reordered_indices[1] = shape.mesh.indices[i + 2];
					reordered_indices[2] = shape.mesh.indices[i + 1];
				}

				for (auto& index : reordered_indices)
				{
					XMFLOAT3 pos = XMFLOAT3(
						obj_attrib.vertices[index.vertex_index * 3 + 0],
						obj_attrib.vertices[index.vertex_index * 3 + 1],
						obj_attrib.vertices[index.vertex_index * 3 + 2]
					);

					XMFLOAT3 nor = XMFLOAT3(0, 0, 0);
					if (!obj_attrib.normals.empty())
					{
						nor = XMFLOAT3(
							obj_attrib.normals[index.normal_index * 3 + 0],
							obj_attrib.normals[index.normal_index * 3 + 1],
							obj_attrib.normals[index.normal_index * 3 + 2]
						);
					}

					XMFLOAT2 tex = XMFLOAT2(0, 0);
					if (index.texcoord_index >= 0 && !obj_attrib.texcoords.empty())
					{
						tex = XMFLOAT2(
							obj_attrib.texcoords[index.texcoord_index * 2 + 0],
							1 - obj_attrib.texcoords[index.texcoord_index * 2 + 1]
						);
					}

					int materialIndex = std::max(0, shape.mesh.material_ids[i / 3]); // this indexes the material library
					if (registered_materialIndices.count(materialIndex) == 0)
					{
						registered_materialIndices[materialIndex] = (int)mesh.subsets.size();
						mesh.subsets.push_back(MeshComponent::MeshSubset());
						mesh.subsets.back().materialID = materialLibrary[materialIndex];
						mesh.subsets.back().indexOffset = (uint32_t)mesh.indices.size();
					}

					if (transform_to_LH)
					{
						pos.z *= -1;
						nor.z *= -1;
					}

					// eliminate duplicate vertices by means of hashing:
					size_t vertexHash = 0;
					wi::helper::hash_combine(vertexHash, index.vertex_index);
					wi::helper::hash_combine(vertexHash, index.normal_index);
					wi::helper::hash_combine(vertexHash, index.texcoord_index);
					wi::helper::hash_combine(vertexHash, materialIndex);

					if (uniqueVertices.count(vertexHash) == 0)
					{
						uniqueVertices[vertexHash] = (uint32_t)mesh.vertex_positions.size();
						mesh.vertex_positions.push_back(pos);
						mesh.vertex_normals.push_back(nor);
						mesh.vertex_uvset_0.push_back(tex);
					}
					mesh.indices.push_back(uniqueVertices[vertexHash]);
					mesh.subsets.back().indexCount++;
				}
			}
			mesh.CreateRenderData();
		}
		*/
	}
	else
	{
		wi::helper::messageBox("FBX import failed! Check backlog for errors!", "Error!");
	}
}

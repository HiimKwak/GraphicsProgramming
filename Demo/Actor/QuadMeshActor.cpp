#include "QuadMeshActor.h"

#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"

#include "Texture/Texture.h"

#include "Resource/MeshLoader.h"
#include "Resource/TextureLoader.h"

using namespace Craft;

QuadMeshActor::QuadMeshActor()
{
	MeshLoader::Get().GetMesh("Quad.obj", mesh);

	//shader = std::make_shared<Shader>(L"Default");
	shader = std::make_shared<TextureMappingShader>("T_coord.png");

	//std::shared_ptr<Texture> texture = std::make_shared<Texture>("T_coord.png");
	//std::weak_ptr<Texture> texture;
	//TextureLoader::Get().Load("T_coord.png", texture);
}

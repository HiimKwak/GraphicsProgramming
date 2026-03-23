#include "QuadMeshActor.h"

#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"

#include "Texture/Texture.h"

#include "Resource/MeshLoader.h"
#include "Resource/TextureLoader.h"

#include "Math/Matrix4.h"
#include "Math/Transform.h"
#include "Graphics/StaticMesh.h"

using namespace Craft;

QuadMeshActor::QuadMeshActor()
{
	MeshLoader::Get().GetMesh("Sphere.obj", mesh);

	//shader = std::make_shared<Shader>(L"Default");
	shader = std::make_shared<TextureMappingShader>("T_coord.png");

	//std::shared_ptr<Texture> texture = std::make_shared<Texture>("T_coord.png");
	//std::weak_ptr<Texture> texture;
	//TextureLoader::Get().Load("T_coord.png", texture);
}

void QuadMeshActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	static float scale = 1.0f;
	static float direction = 1.0f;

	scale += 0.5 * direction * deltaTime;
	if (scale >= 1.2f)
		direction = -1.0f;
	else if (scale <= 0.8f)
		direction = 1.0f;

	static float rotation = 0.0f;
	rotation += 60.0f * deltaTime;

	static float xPosition = 0.0f;
	xPosition += 1.0f * direction * deltaTime;

	//transform->rotation.z = rotation;
	//transform->scale = Vector3(scale, scale, scale);
	//transform->position.x = xPosition;
}

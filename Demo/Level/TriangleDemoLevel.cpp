#include "TriangleDemoLevel.h"
#include "Actor/TriangleMeshActor.h"
#include "Actor/QuadMeshActor.h"
#include "Actor/CameraActor.h"
#include "Actor/LightActor.h"
#include "Actor/CameraMovementActor.h"
#include "Math/Transform.h"

using namespace Craft;

void TriangleDemoLevel::OnInitialized()
{
	Level::OnInitialized();

	//SpawnActor<TriangleMeshActor>();
	std::shared_ptr<QuadMeshActor> quad = SpawnActor<QuadMeshActor>();
	quad->transform->position.x = 0.5f;

	std::shared_ptr<QuadMeshActor> quad2 = SpawnActor<QuadMeshActor>();
	quad2->transform->position.x = -0.5f;

	std::shared_ptr<CameraMovementActor> camera = SpawnActor<CameraMovementActor>();
	camera->transform->position.z = -2.0f;

	std::shared_ptr<LightActor> light = SpawnActor<LightActor>();
	light->transform->position = Vector3(-500.0f, 500.0f, -500.0f);
	light->SetColor(Vector3(1.0f, 1.0f, 0.0f));
}
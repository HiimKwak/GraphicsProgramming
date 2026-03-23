#include "TriangleDemoLevel.h"
#include "Actor/TriangleMeshActor.h"
#include "Actor/QuadMeshActor.h"
#include "Actor/CameraActor.h"
#include "Actor/CameraMovementActor.h"
#include "Math/Transform.h"

using namespace Craft;

void TriangleDemoLevel::OnInitialized()
{
	Level::OnInitialized();

	//SpawnActor<TriangleMeshActor>();
	SpawnActor<QuadMeshActor>();
	std::shared_ptr<CameraMovementActor> camera = SpawnActor<CameraMovementActor>();
	camera->transform->position.z = -2.0f;
}
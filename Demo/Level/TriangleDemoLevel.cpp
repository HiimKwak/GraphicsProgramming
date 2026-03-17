#include "TriangleDemoLevel.h"
#include "Actor/TriangleMeshActor.h"
#include "Actor/QuadMeshActor.h"
#include "Actor/CameraActor.h"
#include "Math/Transform.h"

using namespace Craft;

void TriangleDemoLevel::OnInitialized()
{
	Level::OnInitialized();

	//SpawnActor<TriangleMeshActor>();
	SpawnActor<QuadMeshActor>();
	std::shared_ptr<CameraActor> camera = SpawnActor<CameraActor>();
	camera->transform->position.z = -2.0f;
}
#include "TriangleDemoLevel.h"
#include "Actor/TriangleMeshActor.h"

void TriangleDemoLevel::OnInitialized()
{
	Level::OnInitialized();

	SpawnActor<TriangleMeshActor>();
}
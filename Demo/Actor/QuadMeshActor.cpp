#include "QuadMeshActor.h"
#include "Resource/MeshLoader.h"
#include "Shader/Shader.h"

using namespace Craft;

QuadMeshActor::QuadMeshActor()
{
	MeshLoader::Get().GetMesh("Quad.obj", mesh);

	shader = std::make_shared<Shader>(L"Default");
}

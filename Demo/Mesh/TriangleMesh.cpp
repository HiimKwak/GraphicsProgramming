#include "TriangleMesh.h"
#include "Graphics/Vertex.h"

using namespace Craft;

TriangleMesh::TriangleMesh()
{
	// 정점 데이터(점 3개)
	Vertex vertices[] =
	{
		Vertex(Vector3(0.0f, 0.5f, 0.1f)),
		Vertex(Vector3(0.5f, -0.5f, 0.1f)),
		Vertex(Vector3(-0.5f, -0.5f, 0.1f)),
	};

	// 삼각형 조합할 떄 사용할 순서 지정
	uint32_t indices[] = { 0, 1, 2 };

	StaticMesh::Initialize(
		vertices, _countof(vertices), Vertex::Stride(), indices, _countof(indices)
	);
}
#pragma once

#include "Core/Common.h"
#include <stdint.h>
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Craft
{
	// mesh, vertex shader에서 사용할 정점 클래스
	class CRAFT_API Vertex
	{
	public:
		Vector3 position;
		Vector2 texCoord; // texture coordinates, uv coords
		Vector3 normal;
		Vector3 tangent;
		Vector3 bitangent;

		Vertex(
			const Vector3& position,
			const Vector2& texCoord = Vector2::Zero,
			const Vector3& normal = Vector3::Zero
		);
		~Vertex() = default;

		static uint32_t Stride() { return sizeof(Vertex); }
	};
}
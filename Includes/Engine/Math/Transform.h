#pragma once

#include "Core/Common.h"
#include "Matrix4.h"
#include <d3d11.h>

namespace Craft
{
	class CRAFT_API Transform
	{
	public:
		Transform();
		~Transform();

		void Update();
		void Bind();

	public:
		Vector3 position = Vector3::Zero;
		Vector3 rotation = Vector3::Zero;
		Vector3 scale = Vector3::One;

	private:
		Matrix4 transformMatrix;
		ID3D11Buffer* constantBuffer = nullptr; // dx resource transporting matrix to shader
	};
}

#pragma once

#include "Actor.h"
#include "Math/Matrix4.h"

namespace Craft
{
	// provides camera transportation matrix
	class CRAFT_API CameraActor : public Actor
	{
	public:
		CameraActor(float fieldOfView = 60.0f, float nearDistance = 0.1f, float farDistance = 10000.0f);
		virtual ~CameraActor();

	protected:
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

	protected:
		Matrix4 viewMatrix; // (RT)^(-1) = T^(-1) * R^(-1)

		Matrix4 projectionMatrix;
		float fieldOfView = 0.0f, width = 0.0f, height = 0.0f, nearDistance = 0.0f, farDistance = 0.0f;
	};
}


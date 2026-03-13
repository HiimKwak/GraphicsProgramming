#pragma once

#include "Actor.h"
#include "Math/Matrix4.h"

namespace Craft
{
	// provides camera transportation matrix
	class CRAFT_API CameraActor : public Actor
	{
	public:
		CameraActor();
		~CameraActor();

		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

	private:
		Matrix4 cameraMatrix; // (RT)^(-1) = T^(-1) * R^(-1)

	};
}


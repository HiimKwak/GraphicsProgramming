#include "CameraActor.h"
#include "Math/Transform.h"

namespace Craft
{
	CameraActor::CameraActor()
	{

	}

	CameraActor::~CameraActor()
	{

	}

	void CameraActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Matrix4 translation = Matrix4::Translation(transform->position);
		Matrix4 rotation = Matrix4::Rotation(transform->rotation);
		cameraMatrix = Matrix4::Inverse(translation) * Matrix4::Inverse(rotation);
	}

	void CameraActor::Draw()
	{
		Actor::Draw();
	}
}
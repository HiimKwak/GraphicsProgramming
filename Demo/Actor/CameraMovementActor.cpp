#include "CameraMovementActor.h"
#include "Core/Input.h"
#include "Math/Transform.h"

using namespace Craft;

CameraMovementActor::CameraMovementActor()
{
}

void CameraMovementActor::Tick(float deltaTime)
{
	CameraActor::Tick(deltaTime);

	if (Input::Get().IsKey(VK_ESCAPE))
		QuitGame();

	if (Input::Get().IsKey(VK_RIGHT) || Input::Get().IsKey('D'))
		transform->position = transform->position + transform->Right() * deltaTime * moveSpeed;
	if (Input::Get().IsKey(VK_LEFT) || Input::Get().IsKey('A'))
		transform->position = transform->position - transform->Right() * deltaTime * moveSpeed;
	if (Input::Get().IsKey(VK_UP) || Input::Get().IsKey('W'))
		transform->position = transform->position + transform->Forward() * deltaTime * moveSpeed;
	if (Input::Get().IsKey(VK_DOWN) || Input::Get().IsKey('S'))
		transform->position = transform->position - transform->Forward() * deltaTime * moveSpeed;
	if (Input::Get().IsKey('Q'))
		transform->position = transform->position + transform->Up() * deltaTime * moveSpeed;
	if (Input::Get().IsKey('E'))
		transform->position = transform->position - transform->Up() * deltaTime * moveSpeed;

	if (Input::Get().IsButton(0))
	{
		transform->rotation.y += dragSpeedOffset * Input::Get().GetMouseDeltaX();
		transform->rotation.x += dragSpeedOffset * Input::Get().GetMouseDeltaY();
	}
}

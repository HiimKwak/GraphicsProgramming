#include "Actor.h"
#include "Graphics/Renderer.h"
#include "Math/Transform.h"

namespace Craft
{
	Actor::Actor() : transform(std::make_shared<Transform>())
	{
	}

	Actor::~Actor()
	{
	}

	void Actor::BeginPlay()
	{
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{
		transform->Update();
	}

	void Actor::Draw()
	{
		if (!mesh.lock())
			return;

		Renderer::Get().Submit(mesh.lock(), shader, transform);
	}

	void Actor::SetOwner(std::weak_ptr<Level> newOwner)
	{
		owner = newOwner;
	}
}
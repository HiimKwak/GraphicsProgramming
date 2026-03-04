#include "Actor.h"
#include "Graphics/Renderer.h"

namespace Craft
{
	Actor::Actor()
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
	}

	void Actor::Draw()
	{
		Renderer::Get().Submit(mesh, shader);
	}

	void Actor::SetOwner(std::weak_ptr<Level> newOwner)
	{
		owner = newOwner;
	}
}
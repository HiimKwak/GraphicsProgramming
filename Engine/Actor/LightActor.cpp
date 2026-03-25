#include "LightActor.h"
#include "Graphics/Renderer.h"
#include "Math/Transform.h"

namespace Craft
{
	LightActor::LightActor()
	{

	}

	void LightActor::Draw()
	{
		Actor::Draw();

		Renderer::Get().UpdateLightData(transform->position, intensity, color);
	}
}
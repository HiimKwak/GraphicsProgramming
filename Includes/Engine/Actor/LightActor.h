#pragma once

#include "actor/Actor.h"
#include "Math/Vector3.h"

namespace Craft
{
	class CRAFT_API LightActor : public Actor
	{
	public:
		LightActor();
		~LightActor() = default;

		inline float GetIntensity() const { return intensity; }
		inline void SetIntensity(float newIntensity) { intensity = newIntensity; }

		inline Vector3 GetColor() const { return color; }
		inline void SetColor(const Vector3& newColor) { color = newColor; }

	private:
		virtual void Draw() override;

	private:
		float intensity = 1.0f;
		Vector3 color = Vector3::One;

	};
}


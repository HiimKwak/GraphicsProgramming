#pragma once

#include "Core/Common.h"

namespace Craft
{
	class CRAFT_API Vector2
	{
	public:
		float x = 0.0f, y = 0.0f;

		Vector2(float x = 0.0f, float y = 0.0f);
		~Vector2() = default;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(const Vector2& other) const;
		Vector2 operator*(float scale) const;

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;
	};
}


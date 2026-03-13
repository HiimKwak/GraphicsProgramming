#pragma once

#include "Core/Common.h"

namespace Craft
{
	class CRAFT_API Vector3
	{
	public:
		float x = 0.f, y = 0.f, z = 0.f;

		Vector3(float x = 0.f, float y = 0.f, float z = 0.f);
		~Vector3() = default;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(const Vector3& other) const;
		Vector3 operator*(float scale) const;

		friend CRAFT_API float Dot(const Vector3& left, const Vector3& right);
		friend CRAFT_API Vector3 Cross(const Vector3& left, const Vector3& right);

		static Vector3 Zero;
		static Vector3 One;
		static Vector3 Right;
		static Vector3 Up;
		static Vector3 Forward;
	};
}

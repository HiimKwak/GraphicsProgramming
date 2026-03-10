#include "Vector3.h"

namespace Craft
{
	Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
	Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);

	Vector3::Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 Vector3::operator*(float scale) const
	{
		return Vector3(x * scale, y * scale, z * scale);
	}
}
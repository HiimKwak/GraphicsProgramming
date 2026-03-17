#include "Vector3.h"
#include <cmath>
#include <cassert>

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

	float Dot(const Vector3& left, const Vector3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
		// A Dot B == A vec * B vec * Cos(Theta)
	}
	Vector3 Cross(const Vector3& left, const Vector3& right)
	{
		// Cross Product: A × B = |A| * |B| * sin(θ) * n (where n is the normal vector)
		// Note: Order matters, not commutative (A × B != B × A, actually A × B = -(B × A))
		// sin(θ) is used for left/right determination in games (perpendicular component)
		// (cos(θ) in Dot product is used for front/back determination - parallel component)
		return Vector3(
			(left.y * right.z) - (left.z * right.y),
			(left.z * right.x) - (left.x * right.z),
			(left.x * right.y) - (left.y * right.x)
		);
	}

	float Vector3::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 Vector3::Normalized() const
	{
		float length = Length();
		assert(length > 0);
		return Vector3(x / length, y / length, z / length);
	}
}
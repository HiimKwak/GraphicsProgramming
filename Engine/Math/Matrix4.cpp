#include "Matrix4.h"
#include <string>
#include <cmath>

namespace Craft
{
	Matrix4 Matrix4::Identity = Matrix4();

	Matrix4::Matrix4()
	{
		memset(elements, 0, sizeof(float) * 16);

		m00 = m11 = m22 = m33 = 1;
	}

	Matrix4::Matrix4(const Matrix4& other)
	{
		memcpy(elements, other.elements, sizeof(float) * 16);
	}

	Matrix4 Matrix4::Transpose(const Matrix4& matrix) // switch matrix between row and column
	{
		Matrix4 m = matrix;
		std::swap<float>(m.m01, m.m10);
		std::swap<float>(m.m02, m.m20);
		std::swap<float>(m.m03, m.m30);

		std::swap<float>(m.m12, m.m21);
		std::swap<float>(m.m13, m.m31);

		std::swap<float>(m.m23, m.m32);

		return m;
	}

	Matrix4 Matrix4::Translation(float x, float y, float z)
	{
		Matrix4 m;

		m.m00 = 1.0f;	m.m01 = 0.0f;	m.m02 = 0.0f;	m.m03 = 0.0f;
		m.m10 = 0.0f;	m.m11 = 1.0f;	m.m12 = 0.0f;	m.m13 = 0.0f;
		m.m20 = 0.0f;	m.m21 = 0.0f;	m.m22 = 1.0f;	m.m23 = 0.0f;

		m.m30 = x;		m.m31 = y;		m.m32 = z;		m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::Translation(const Vector3& position)
	{
		return Translation(position.x, position.y, position.z);
	}

	Matrix4 Matrix4::Rotation(float x, float y, float z)
	{
		// x > y > z
		// Pitch > Yaw > Roll
		return RotationX(x) * RotationY(y) * RotationZ(z);
	}

	Matrix4 Matrix4::Rotation(const Vector3& rotation)
	{
		return Rotation(rotation.x, rotation.y, rotation.z);
	}

	Matrix4 Matrix4::RotationX(float angle)
	{
		Matrix4 m;

		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);

		m.m00 = 1.0f; m.m01 = 0.0f; m.m02 = 0.0f; m.m03 = 0.0f;
		m.m10 = 0.0f; m.m11 = cosAngle; m.m12 = sinAngle; m.m13 = 0.0f;
		m.m20 = 0.0f; m.m21 = -sinAngle; m.m22 = cosAngle; m.m23 = 0.0f;
		m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::RotationY(float angle)
	{
		Matrix4 m;

		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);

		m.m00 = cosAngle; m.m01 = 0.0f; m.m02 = -sinAngle; m.m03 = 0.0f;
		m.m10 = 0.0f; m.m11 = 1.0f; m.m12 = 0.0f; m.m13 = 0.0f;
		m.m20 = sinAngle; m.m21 = 0.0f; m.m22 = cosAngle; m.m23 = 0.0f;
		m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::RotationZ(float angle)
	{
		Matrix4 m;

		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);

		m.m00 = cosAngle; m.m01 = sinAngle; m.m02 = 0.0f; m.m03 = 0.0f;
		m.m10 = -sinAngle; m.m11 = cosAngle; m.m12 = 0.0f; m.m13 = 0.0f;
		m.m20 = 0.0f; m.m21 = 0.0f; m.m22 = 1.0f; m.m23 = 0.0f;
		m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::Scale(float x, float y, float z)
	{
		Matrix4 m;

		m.m00 = x; m.m01 = 0.0f; m.m02 = 0.0f; m.m03 = 0.0f;
		m.m10 = 0.0f; m.m11 = y; m.m12 = 0.0f; m.m13 = 0.0f;
		m.m20 = 0.0f; m.m21 = 0.0f; m.m22 = z; m.m23 = 0.0f;
		m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::Scale(const Vector3& scale)
	{
		return Scale(scale.x, scale.y, scale.z);
	}

	Matrix4 Matrix4::Scale(float scale)
	{
		return Scale(scale, scale, scale);
	}

	Matrix4& Matrix4::operator=(const Matrix4& other)
	{
		memcpy(elements, other.elements, sizeof(float) * 16);
		return *this;
	}

	Matrix4 Matrix4::operator*(const Matrix4& other) const
	{
		Matrix4 m;

		// first row
		m.m00
			= m00 * other.m00
			+ m01 * other.m10
			+ m02 * other.m20
			+ m03 * other.m30;

		m.m01
			= m00 * other.m01
			+ m01 * other.m11
			+ m02 * other.m21
			+ m03 * other.m31;

		m.m02
			= m00 * other.m02
			+ m01 * other.m12
			+ m02 * other.m22
			+ m03 * other.m32;

		m.m03
			= m00 * other.m03
			+ m01 * other.m13
			+ m02 * other.m23
			+ m03 * other.m33;

		// second row
		m.m10
			= m10 * other.m00
			+ m11 * other.m10
			+ m12 * other.m20
			+ m13 * other.m30;

		m.m11
			= m10 * other.m01
			+ m11 * other.m11
			+ m12 * other.m21
			+ m13 * other.m31;

		m.m12
			= m10 * other.m02
			+ m11 * other.m12
			+ m12 * other.m22
			+ m13 * other.m32;

		m.m13
			= m10 * other.m03
			+ m11 * other.m13
			+ m12 * other.m23
			+ m13 * other.m33;

		// third row
		m.m20
			= m20 * other.m00
			+ m21 * other.m10
			+ m22 * other.m20
			+ m23 * other.m30;

		m.m21
			= m20 * other.m01
			+ m21 * other.m11
			+ m22 * other.m21
			+ m23 * other.m31;

		m.m22
			= m20 * other.m02
			+ m21 * other.m12
			+ m22 * other.m22
			+ m23 * other.m32;

		m.m23
			= m20 * other.m03
			+ m21 * other.m13
			+ m22 * other.m23
			+ m23 * other.m33;

		// fourth row
		m.m30
			= m30 * other.m00
			+ m31 * other.m10
			+ m32 * other.m20
			+ m33 * other.m30;

		m.m31
			= m30 * other.m01
			+ m31 * other.m11
			+ m32 * other.m21
			+ m33 * other.m31;

		m.m32
			= m30 * other.m02
			+ m31 * other.m12
			+ m32 * other.m22
			+ m33 * other.m32;

		m.m33
			= m30 * other.m03
			+ m31 * other.m13
			+ m32 * other.m23
			+ m33 * other.m33;

		return m;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector3 operator*(const Matrix4& m, const Vector3& v)
	{
		// Mathematically incorrect: Matrix * Vector should treat vector as column vector,
		// but this implementation forwards to Vector * Matrix (row vector convention).
		// Works consistently because the entire codebase uses row-major/row-vector style (DirectX convention).
		return v * m; //  
	}

	Vector3 operator*(const Vector3& v, const Matrix4& m)
		// Vector3 needs to be considered as 1x3 matrix
		// results gonna be 1x3 Vector( 1x3() * 4x4() )
	{
		Vector3 retV;
		retV.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + 1.0f * m.m30;
		retV.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + 1.0f * m.m31;
		retV.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + 1.0f * m.m32;
		//retV.w = ...;

		return retV;
	}
}
#pragma once
#include "Core/Common.h"
#include "Vector3.h"

namespace Craft
{
	class CRAFT_API Matrix4 // row-major matrix: CPU friendly(GPU: column-major)
		// SIMD(Single Instruction, Multiple Data), MMX/SSE
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& other);
		~Matrix4() = default;

		static Matrix4 Transpose(const Matrix4& matrix);

		static Matrix4 Translation(float x, float y, float z);
		static Matrix4 Translation(const Vector3& position);

		static Matrix4 Rotation(float x, float y, float z);
		static Matrix4 Rotation(const Vector3& rotation);
		static Matrix4 RotationX(float angle);
		static Matrix4 RotationY(float angle);
		static Matrix4 RotationZ(float angle);

		static Matrix4 Scale(float x, float y, float z);
		static Matrix4 Scale(const Vector3& scale);
		static Matrix4 Scale(float scale);

		Matrix4& operator=(const Matrix4& other);
		Matrix4 operator*(const Matrix4& other) const;
		Matrix4& operator*=(const Matrix4& other);

		friend CRAFT_API Vector3 operator*(const Matrix4& m, const Vector3& v);
		friend CRAFT_API Vector3 operator*(const Vector3& v, const Matrix4& m);

		static Matrix4 Identity;
		static constexpr float degreeToRadian = 3.141592f / 180.0f;
		static constexpr float radianToDegree = 180.0f / 3.141592f;

	private:
		union // share memory space, most largest variable
		{
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			float elements[4 * 4] = {};
		};
	};
}


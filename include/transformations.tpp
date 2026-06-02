#include "linalg/include/mat.h"
#include "linalg/include/vec.h"
#include "quat.h"

namespace tl3d
{
	using namespace linalg;

	template<size_t L, typename T>
	mat<L, L, T> trans(const mat<L, L, T>& m, const vec<L - 1, T>& t)
	{
		mat ret(m);

		for (int i = 0; i < m.num_rows - 1; ++i)
			ret[ret.num_cols - 1][i] += t[i];

		return ret;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	mat<L, L, T> scale(const mat<L, L, T>& m, const U& s)
	{
		mat ret(m);

		for (int i = 0; i < m.num_cols - 1; ++i)
			ret[i][i] *= s;

		return ret;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	mat<L, L, T> scale(const mat<L, L, T>& m, const vec<L - 1, U>& s)
	{
		mat ret(m);

		for (int i = 0; i < m.num_cols - 1; ++i)
			ret[i][i] *= s[i];

		return ret;
	}

	template<typename T>
	mat<4, 4, T> rotate(const mat<4, 4, T>& m, const quat<T>& quat)
	{
		T w = quat.w;
		T x = quat.x;
		T y = quat.y;
		T z = quat.z;

		mat<4, 4, T> rotation_matrix(
			vec<4, T>(1 - 2 * (y * y + z * z), 2 * x * y - 2 * z * w, 2 * x * z + 2 * y * w, 0),
			vec<4, T>(2 * x * y + 2 * z * w, 1 - 2 * (x * x + z * z), 2 * y * z - 2 * x * w, 0),
			vec<4, T>(2 * x * z - 2 * y * w, 2 * y * z + 2 * x * w, 1 - 2 * (x * x + y * y), 0),
			vec<4, T>(0, 0, 0, 1)
		);

		return rotation_matrix * m;
	}

	template<typename T>
	mat<4, 4, T> rotate(const mat<4, 4, T>& m, T angle, vec<3, T> axis)
	{
		axis = norm(axis);

		T x = axis.x;
		T y = axis.y;
		T z = axis.z;
		T a = cos(angle);
		T b = sin(angle);
		T s = (1 - cos(angle));

		mat<4, 4, T> rotation_matrix(
			vec<4, T>(a + x * x * s, y * x * s + z * b, z * x * s - y * b, 0),
			vec<4, T>(x * y * s - z * b, a + y * y * s, z * y * s + x * b, 0),
			vec<4, T>(x * z * s + y * b, y * z * s - x * b, a + z * z * s, 0),
			vec<4, T>(0, 0, 0, 1)
		);

		return rotation_matrix * m;
	}

	inline mat<4, 4, float> perspective(float fov, float aspect, float near, float far)
	{
		float height = 2 * near * tan(fov / 2);
		float width = aspect * height;
		float top = height / 2;
		float bottom = -height / 2;
		float left = -width / 2;
		float right = width / 2;

		return mat<4, float>(
			{ near / right, 0, 0, 0 },
			{ 0, near / top, 0, 0 },
			{ 0, 0, -(far + near) / (far - near), -1 },
			{ 0, 0, -2 * far * near / (far - near), 0 }
		);
	}

	inline mat<4, 4, float> orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		return mat<4, float>(
			{ 2.0f / (right - left), 0, 0, 0 },
			{ 0, 2.0f / (top - bottom), 0, 0 },
			{ 0, 0, -2.0f / (far - near), 0 },
			{ -2.0f * left / (right - left) - 1.0f, -2.0f * bottom / (top - bottom) - 1.0f, -2.0f * near / (far - near) - 1.0f, 1 }
		);
	}
}
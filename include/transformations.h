#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "linalg/include/mat.h"
#include "linalg/include/vec.h"

namespace tl3d
{
	using namespace linalg;

	template<size_t L, typename T>
	mat<L, L, T> trans(const mat<L, L, T>& m, const vec<L - 1, T>& t);

	template<size_t L, typename T>
	mat<L, L, T> scale(const mat<L, L, T>& m, const T& s);

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T> 
	mat<L, L, T> scale(const mat<L, L, T>& m, const vec<L - 1, U>& s);

	template<typename T>
	mat<4, 4, T> rotate(const mat<4, 4, T>& m, const quat<T>& quat);

	template<typename T>
	mat<4, 4, T> rotate(const mat<4, 4, T>& m, T angle, vec<3, T> axis);

	inline mat<4, 4, float> perspective(float fov, float aspect, float near, float far);

	inline mat<4, 4, float> orthographic(float left, float right, float bottom, float top, float near, float far);
}

#include "transformations.tpp"

#endif
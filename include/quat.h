#ifndef QUAT_H
#define QUAT_H

#include "linalg/include/vec.h"

namespace tl3d
{
	using namespace linalg;

	template<typename T>
	class quat
	{
	public:
		const static size_t length = 4;

		T w, x, y, z;

		quat()
			: w{ 1 }, x{ 0 }, y{ 0 }, z{ 0 }
		{}

		quat(T w, T x, T y, T z)
			: w{ w }, x{ x }, y{ y }, z{ z }
		{}

		quat(T angle, vec<3, T> axis)
			: w{cos(angle / 2)}, x{axis.x * sin(angle / 2)}, y{axis.y * sin(angle/2)}, z{axis.z * sin(angle/2)}
		{}

		quat(const quat<T>& other)
			: w{ other.w }, x{ other.x }, y{ other.y }, z{ other.z }
		{}

		quat(const vec<4, T>& v)
			: w{ v[0] }, x{ v[1] }, y{ v[2] }, z{ v[3] }
		{}

		quat(const vec_initializer<4, T>& init);

		quat<T>& operator=(const quat<T>& other);

		T& operator[](size_t idx) const;

		operator vec<4, T>() const;
	};
}

#include "quat.tpp"

#endif
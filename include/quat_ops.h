#ifndef QUAT_OPS_H
#define QUAT_OPS_H

#include "quat.h"

namespace tl3d
{
	using namespace linalg;

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator+=(quat<T>& q, const U& val)
	{
		apply(q, [val](T& elem) {elem += val; });
		return q;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator+(const quat<T>& q, const U& val)
	{
		quat<T> new_vec(q);
		new_vec += val;
		return new_vec;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator+(const U& val, const quat<T>& q)
	{
		return val + q;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator+=(quat<T>& q1, const quat<U>& q2)
	{
		apply_elementwise(q1, [q2](T& elem_1, const T& elem_2) {elem_1 += elem_2; }, q2);
		return q1;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator+(const quat<T>& q1, const quat<U>& q2)
	{
		quat<T> new_vec(q1);
		new_vec += q2;
		return new_vec;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator-=(quat<T>& q, const U& val)
	{
		apply(q, [val](T& elem) {elem -= val; });
		return q;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator-(const quat<T>& q, const U& val)
	{
		quat<T> new_vec(q);
		new_vec -= val;
		return new_vec;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator-(const U& val, const quat<T>& q)
	{
		quat<T> new_vec;
		return new_vec + val - q;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator-=(quat<T>& q1, const quat<U>& q2)
	{
		apply_elementwise(q1, [q2](T& elem_1, const T& elem_2) {elem_1 -= elem_2; }, q2);
		return q1;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator-(const quat<T>& q1, const quat<U>& q2)
	{
		quat<T> new_vec(q1);
		new_vec -= q2;
		return new_vec;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator*=(quat<T>& q1, const U& val)
	{
		apply(q1, [val](T& elem) {elem *= val; });
		return q1;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator*(const quat<T>& q, const U& val)
	{
		quat<T> new_vec(q);
		new_vec *= val;
		return new_vec;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator*(const U& val, const quat<T>& q)
	{
		return q * val;
	}

	template<typename T, typename U>
	quat<T>& operator*=(quat<T>& q1, const quat<U>& q2) requires std::convertible_to<U, T>
	{
		quat<T> new_quat(q1);

		new_quat.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
		new_quat.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
		new_quat.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
		new_quat.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

		q1 = new_quat;

		return q1;
	}

	template<typename T, typename U>
	quat<T> operator*(const quat<T>& q1, const quat<U>& q2) requires std::convertible_to<U, T>
	{
		quat<T> new_quat(q1);
		new_quat *= q2;
		return new_quat;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator/=(quat<T>& q1, const U& val)
	{
		apply(q1, [val](T& elem) {elem /= val; });
		return q1;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator/(const quat<T>& q, const U& val)
	{
		quat<T> new_vec(q);
		new_vec /= val;
		return new_vec;
	}

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator/(const U& val, const quat<T>& q)
	{
		quat<T> new_vec;
		apply_elementwise([val](T& elem1, const T& elem2) {elem1 = val / elem2; }, q);
		return new_vec;
	}

	// Apply a unary operation to every element in the vector
	template<typename T, typename F>
	void apply(quat<T>& q, F func)
	{
		for (size_t i = 0; i < q.length; ++i)
			func(q[i]);
	}

	// Apply a binary operation between every element of this vector and every element of other
	template<typename T, typename U, typename F>
	void apply_elementwise(quat<T>& q, F func, const quat<U>& other)
		requires std::convertible_to<U, T>
	{
		for (size_t i = 0; i < q.length; ++i)
			func(q[i], other[i]);
	}

	template<typename T>
	T mag(quat<T> q)
	{
		T acc = 0;

		for (int i = 0; i < q.length; ++i)
			acc += std::pow(q[i], 2);

		T mag = std::sqrt(acc);

		return mag;
	}

	template<typename T>
	quat<T> norm(quat<T> q)
	{
		T m = mag(q);

		if (m == 0)
			return q;

		quat<T> ret = q / m;

		return ret;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const quat<T>& q)
	{
		for (int i = 0; i < q.length; ++i)
			std::cout << q[i] << "\t";

		return os;
	}
}

#endif
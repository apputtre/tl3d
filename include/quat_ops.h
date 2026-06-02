#ifndef QUAT_OPS_H
#define QUAT_OPS_H

#include "quat.h"

namespace tl3d
{
	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator+=(quat<T>& q, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator+(const quat<T>& q, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator+(const U& val, const quat<T>& v);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator+=(quat<T>& q1, const quat<U>& q2);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator+(const quat<T>& q1, const quat<U>& q2);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator-=(quat<T>& q, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator-(const quat<T>& q, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator-(const U& val, const quat<T>& q);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator-=(quat<T>& q1, const quat<U>& q2);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator-(const quat<T>& q1, const quat<U>& q2);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator*=(quat<T>& q1, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator*(const quat<T>& q, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator*(const U& val, const quat<T>& q);

	template<typename T, typename U>
	quat<T>& operator*=(quat<T>& q1, const quat<U>& q2) requires std::convertible_to<U, T>;

	template<typename T, typename U>
	quat<T> operator*(const quat<T>& q1, const quat<U>& q2) requires std::convertible_to<U, T>;

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T>& operator/=(quat<T>& q1, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator/(const quat<T>& q, const U& val);

	template<typename T, typename U> requires std::convertible_to<U, T>
	quat<T> operator/(const U& val, const quat<T>& q);

	// Apply a unary operation to every element in the vector
	template<typename T, typename F>
	void apply(quat<T>& q, F func);

	// Apply a binary operation between every element of this vector and every element of other
	template<typename T, typename U, typename F>
	void apply_elementwise(quat<T>& q, F func, const quat<U>& other) requires std::convertible_to<U, T>;

	template<typename T>
	T mag(quat<T> q);

	template<typename T>
	quat<T> norm(quat<T> q);

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const quat<T>& q);
}

#include "quat_ops.tpp"

#endif
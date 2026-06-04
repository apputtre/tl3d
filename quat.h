#ifndef QUAT_H
#define QUAT_H

#include "linalg/vec.h"

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
			:
				w{std::cos(angle/2.0f)},
				x{axis.x*std::sin(angle/2.0f)},
				y{axis.y*std::sin(angle/2.0f)},
				z{axis.z*std::sin(angle/2.0f)}
		{}

		quat(const quat<T>& other)
			: w{ other.w }, x{ other.x }, y{ other.y }, z{ other.z }
		{}

		quat(const vec<4, T>& v)
			: w{ v[0] }, x{ v[1] }, y{ v[2] }, z{ v[3] }
		{}

		quat<T>& operator=(const quat<T>& other)
		{
			w = other.w;
			x = other.x;
			y = other.y;
			z = other.z;

			return *this;
		}

		T& operator[](size_t idx) const
		{
			switch (idx)
			{
			case 0:
				return (T&)w;
				break;
			case 1:
				return (T&)x;
				break;
			case 2:
				return (T&)y;
				break;
			case 3:
				return (T&)z;
				break;
			default:
				throw std::runtime_error("Index out of bounds");
				break;
			}
		}

		operator vec<4, T>() const
		{
			return vec<4, T>(w, x, y, z);
		}

		template<typename U>
			requires std::convertible_to<U, T>
		quat<T>& operator+=(const U& val)
		{
			apply(*this, [val](T& elem) {elem += val; });
			return *this;
		}

		template<typename U>
			requires std::convertible_to<U, T>
		quat<T>& operator+=(const quat<U>& q)
		{
			apply_elementwise(*this, [q](T& elem_1, const T& elem_2) {elem_1 += elem_2; }, q);
			return *this;
		}

		template<typename U>
			requires std::convertible_to<U, T>
		quat<T>& operator-=(const U& val)
		{
			apply(*this, [val](T& elem) {elem -= val; });
			return *this;
		}

		template<typename U>
			requires std::convertible_to<U, T>
		quat<T>& operator*=(const U& val)
		{
			apply(*this, [val](T& elem) {elem *= val; });
			return *this;
		}

		template<typename U>
			requires std::convertible_to<U, T>
		quat<T>& operator*=(const quat<U>& q)
		{

			this->w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
			this->x = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
			this->y = this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x;
			this->z = this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w;

			return (*this);
		}

		template<typename U>
			requires std::convertible_to<U, T>
		quat<T>& operator/=(const U& val)
		{
			apply(*this, [val](T& elem) {elem /= val; });
			return *this;
		}

		auto mag()
		{
			T acc = 0;

			for (int i = 0; i < this->length; ++i)
				acc += std::pow((*this)[i], 2);

			T mag = std::sqrt(acc);

			return mag;
		}

		quat<T> norm()
		{
			T m = mag();

			if (m == 0)
				return *this;

			quat<T> ret = *this / m;
			
			return *this;
		}


	private:
		// Apply a unary operation to every element in the vector
		template<typename F>
		void apply(quat<T>& q, F func)
		{
			for (size_t i = 0; i < q.length; ++i)
				func(q[i]);
		}

		// Apply a binary operation between every element of this vector and every element of other
		template<typename F, typename U>
		void apply_elementwise(quat<T>& q, F func, const quat<U>& other)
			requires std::convertible_to<U, T>
		{
			for (size_t i = 0; i < q.length; ++i)
				func(q[i], other[i]);
		}
	};

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
	quat<T> operator+(const quat<T>& q1, const quat<U>& q2)
	{
		quat<T> new_vec(q1);
		new_vec += q2;
		return new_vec;
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
	quat<T> operator*(const quat<T>& q1, const quat<U>& q2) requires std::convertible_to<U, T>
	{
		quat<T> new_quat(q1);
		new_quat *= q2;
		return new_quat;
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

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const quat<T>& q)
	{
		for (int i = 0; i < q.length; ++i)
			std::cout << q[i] << "\t";

		return os;
	}
}

#endif
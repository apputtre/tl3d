namespace tl3d
{
	template<typename T>
	T& quat<T>::operator[](size_t idx) const
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
			throw new std::exception("Index out of bounds");
			break;
		}
	}

	template<typename T>
	quat<T>& quat<T>::operator=(const quat<T>& other)
	{
		w = other.w;
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	template<typename T>
	quat<T>::quat<T>(const vec_initializer<4, T>& init)
	{
		w = init[0];
		x = init[1];
		y = init[2];
		z = init[3];
	}

	template<typename T>
	quat<T>::operator vec<4, T>() const
	{
		return vec<4, T>(w, x, y, z);
	}
}

#pragma once

#include "Vec.hpp"

namespace pirkk::math {
	template<typename T>
	struct Vec<T, 3> {
		union {
			T data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vec(T x, T y, T z) : x(x), y(y), z(z) {}
		Vec(T v) : Vec(v, v, v) {}
		Vec() : Vec(0) {}
		template<typename U, size_t L> explicit Vec(const Vec<U, L>& other) { for (size_t i = 0; i < 3 && i < L; i++) data[i] = other.data[i]; }

		T& operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
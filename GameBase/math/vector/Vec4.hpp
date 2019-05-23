#pragma once

#include "Vec.hpp"

namespace pirkk::math {
	template<typename T>
	struct Vec<T, 4> {
		union {
			T data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		Vec(T v) : Vec(v, v, v, v) {}
		Vec() : Vec(0) {}
		template<typename U, size_t L> explicit Vec(const Vec<U, L>& other) { for (size_t i = 0; i < 4 && i < L; i++) data[i] = other.data[i]; }

		T& operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
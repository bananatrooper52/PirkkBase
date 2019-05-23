#pragma once

#include "Vec.hpp"

namespace pirkk::math {
	template<typename T>
	struct Vec<T, 2> {
		union {
			T data[2];
			struct { T x, y; };
			struct { T r, g; };
		};

		Vec() : Vec(0) {}
		Vec(T x, T y) : x(x), y(y) {}
		explicit Vec(T v) : Vec(v, v) {}
		template<typename U, size_t L> explicit Vec(const Vec<U, L>& other) { for (size_t i = 0; i < 2 && i < L; i++) data[i] = other.data[i]; }

		T& operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
#pragma once

#include "Vec.hpp"

namespace Pirkk::Math {
	template<typename T>
	struct Vec<T, 3> {
		union {
			T data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vec(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
		Vec(T _v) : Vec(_v, _v, _v) {}
		Vec() : Vec(0) {}
		template<typename U> explicit Vec(const Vec<U, 3> &other) { for (size_t i = 0; i < 3; i++) data[i] = other.data[i]; }

		T &operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
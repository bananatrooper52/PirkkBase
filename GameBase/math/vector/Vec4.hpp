#pragma once

#include "Vec.hpp"

namespace Pirkk::Math {
	template<typename T>
	struct Vec<T, 4> {
		union {
			T data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		Vec(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
		Vec(T _v) : Vec(_v, _v, _v, _v) {}
		Vec() : Vec(0) {}
		template<typename U> explicit Vec(const Vec<U, 4> &other) { for (size_t i = 0; i < 4; i++) data[i] = other.data[i]; }

		T &operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
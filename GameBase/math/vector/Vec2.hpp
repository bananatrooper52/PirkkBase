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

		Vec(T _x, T _y) : x(_x), y(_y) {}
		Vec(T _v) : Vec(_v, _v) {}
		Vec() : Vec(0) {}
		template<typename U> explicit Vec(const Vec<U, 2> &other) { for (size_t i = 0; i < 2; i++) data[i] = other.data[i]; }
		template<typename U> explicit Vec(const Vec<U, 3>& other) { for (size_t i = 0; i < 2; i++) data[i] = other.data[i]; }
		template<typename U> explicit Vec(const Vec<U, 4>& other) { for (size_t i = 0; i < 2; i++) data[i] = other.data[i]; }

		T &operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
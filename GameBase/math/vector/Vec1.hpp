#pragma once

#include "Vec.hpp"

namespace pirkk::math {
	template<typename T>
	struct Vec<T, 1> {
		union {
			T data[1];
			struct { T x; };
			struct { T r; };
		};

		Vec(T x) : Vec(x) {}
		Vec() : Vec(0) {}
		template<typename U, size_t L> explicit Vec(const Vec<U, L>& other) { for (size_t i = 0; i < 1 && i < L; i++) data[i] = other.data[i]; }
		template<typename U> explicit Vec(const U v) { this.x = v; }

		T& operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}
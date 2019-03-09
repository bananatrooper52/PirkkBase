#pragma once

#include "Vec.h"

namespace PirkkBase {
	namespace Math {
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

			T &operator[](size_t i) { return data[i]; }
			T operator[](size_t i) const { return data[i]; }
		};
	}
}
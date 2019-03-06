#pragma once

#include "Vec.h"

namespace PirkkBase {
	template<typename T>
	struct Vec<T, 3> {
		union {
			T data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vec() { for (size_t i = 0; i < 3; i++) data[i] = 0; }
		Vec(T _v) { for (size_t i = 0; i < 3; i++) data[i] = _v; }
		Vec(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }

		T &operator[](size_t i) { return data[i]; }
	};
}
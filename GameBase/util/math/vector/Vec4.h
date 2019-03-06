#pragma once

#include "Vec.h"

namespace PirkkBase {
	template<typename T>
	struct Vec<T, 4> {
		union {
			T data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		Vec() { for (size_t i = 0; i < 4; i++) data[i] = 0; }
		Vec(T _v) { for (size_t i = 0; i < 4; i++) data[i] = _v; }
		Vec(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; }

		T &operator[](size_t i) { return data[i]; }
	};
}
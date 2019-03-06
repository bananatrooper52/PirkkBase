#pragma once

#include "Vec.h"

namespace PirkkBase {
	template<typename T>
	struct Vec<T, 2> {
		union {
			T data[2];
			struct { T x, y; };
			struct { T r, g; };
		};

		Vec() { for (size_t i = 0; i < 2; i++) data[i] = 0; }
		Vec(T _v) { for (size_t i = 0; i < 2; i++) data[i] = _v; }
		Vec(T _x, T _y) { x = _x; y = _y; }

		T &operator[](size_t i) { return data[i]; }
	};
}
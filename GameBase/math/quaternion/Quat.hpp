#pragma once

#include "../matrix/Mat.hpp"

namespace pirkk::math {
	template<typename T>
	struct Quat {
		union {
			T data[4];
			struct { T w, x, y, z; };
		};
		Quat() : w(1), x(0), y(0), z(0) {}
		Quat(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}
		Quat(Mat4<T> m) :
			w(sqrt(1 + m[0][0] + m[1][1] + m[2][2]) / 2),
			x((m[2][1] - m[1][2]) / w / 4),
			y((m[0][2] - m[2][0]) / w / 4),
			z((m[1][0] - m[0][1]) / w / 4) {}
		T& operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};
}

#include "QuatOp.hpp"
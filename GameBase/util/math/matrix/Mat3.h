#pragma once

#include "Mat.h"

namespace PirkkBase {
	template<typename T>
	struct Mat<T, 3, 3> {

		union {
			Vec<T, 3> data[3];
			struct { Vec<T, 3> x, Vec<T, 3> y, Vec<T, 3> z; };
		};

		Mat(Vec<T, 3> _x, Vec<T, 3> _y, Vec<T, 3> _z) : x(_x), y(_y), z(_z) {};
		Mat(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz) : 
			Mat(Vec<T, 3>(xx, xy, xz), 
				Vec<T, 3>(yx, yy, yz), 
				Vec<T, 3>(zx, zy, zz)
			) {}
		Mat(T _v) : Mat(_v, 0, 0, 0, _v, 0, 0, 0, _v) {}
		Mat() : Mat(1) {}
	};
}
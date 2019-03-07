#pragma once

#include "Mat.h"

namespace PirkkBase {
	template<typename T>
	struct Mat<T, 4, 4> {

		union {
			Vec<T, 4> data[4];
			struct { Vec<T, 4> x, Vec<T, 4> y, Vec<T, 4> z, Vec<T, 4> w; };
		};

		Mat(Vec<T, 4> _x, Vec<T, 4> _y, Vec<T, 4> _z, Vec<T, 4> _w) : x(_x), y(_y), z(_z), w(_w) {};
		Mat(T xx, T xy, T xz, T xw, T yx, T yy, T yz, T yw, T zx, T zy, T zz, T zw, T wx, T wy, T wz, T ww) :
			Mat(Vec<T, 4>(xx, xy, xz, xw),
				Vec<T, 4>(yx, yy, yz, yw),
				Vec<T, 4>(zx, zy, zz, zw),
				Vec<T, 4>(wx, wy, wz, ww)
			) {}
		Mat(T _v) : Mat(_v, 0, 0, 0, 0, _v, 0, 0, 0, 0, _v, 0, 0, 0, 0, _v) {}
		Mat() : Mat(1) {}
	};
}
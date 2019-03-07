#pragma once

#include "Mat.h"

namespace PirkkBase {
	template<typename T>
	struct Mat<T, 2, 2> {

		union {
			Vec<T, 2> data[2];
			struct { Vec<T, 2> x, Vec<T, 2> y; };
		};

		Mat(Vec<T, 2> _x, Vec<T, 2> _y) : x(_x), y(_y) {};
		Mat(T xx, T xy, T yx, T yy) : 
			Mat(Vec<T, 2>(xx, xy), 
				Vec<T, 2>(yx, yy)
			) {}
		Mat(T _v) : Mat(_v, 0, 0, _v) {}
		Mat() : Mat(1) {}
	};
}
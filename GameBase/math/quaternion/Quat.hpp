#pragma once

#include "../vector/Vec.hpp"
#include "../matrix/Mat.hpp"

namespace pirkk::math {
	template<typename T>
	class Quat {
		Vec4<T> data;
	};
}
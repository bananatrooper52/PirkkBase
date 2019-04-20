#pragma once

#include "../vector/Vec.hpp"
#include "../matrix/Mat.hpp"

namespace Pirkk::Math {
	template<typename T>
	class Quat {
		Vec4<T> data;
	};
}
#pragma once

#include "../vector/Vec.h"
#include "../matrix/Mat.h"

namespace PirkkBase {
	namespace Math {
		template<typename T>
		class Quat {
			Vec4<T> data;
		};
	}
}
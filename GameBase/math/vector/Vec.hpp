#pragma once

#include <iostream>

namespace pirkk::math {
	template<typename T, size_t L>
	struct Vec {
		T data[L];

		Vec() { for (size_t i = 0; i < L; i++) data[i] = 0; }
		template<typename U> explicit Vec(const Vec<U, L> & other) { for (size_t i = 0; i < L; i++) data[i] = other.data[i]; }
		T& operator[](size_t i) { return data[i]; }
		T operator[](size_t i) const { return data[i]; }
	};

	// Enable printing with std::cout
	template<typename T, size_t L>
	std::ostream& operator<<(std::ostream & out, const Vec<T, L> & vec) {
		out << "[";
		for (size_t i = 0; i < L; i++) {
			out << vec[i];
			if (i < L - 1) out << ", ";
		}
		out << "]";
		return out;
	}
}

#include "Vec1.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "VecOp.hpp"
#include "VecTypes.hpp"
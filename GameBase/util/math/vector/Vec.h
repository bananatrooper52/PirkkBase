#pragma once

#include <ostream>
#include <iostream>

namespace PirkkBase {
	template<typename T, size_t L> struct Vec;
}

namespace PirkkBase {
	template<typename T, size_t L>
	struct Vec {
		T data[L];

		Vec() { for (size_t i = 0; i < L; i++) data[i] = 0; }
		T &operator[](size_t i) { return data[i]; }
	};

	// Enable printing with std::cout
	template<typename T, size_t L>
	std::ostream &operator<<(std::ostream &out, const Vec<T, L> &vec) {
		out << "(";
		for (size_t i = 0; i < L; i++) {
			out << vec.data[i];
			if (i < L - 1) out << ", ";
		}
		out << ")";
		return out;
	}
}
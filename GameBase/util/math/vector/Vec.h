#pragma once

#include <ostream>
#include <iostream>

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
		out << "[";
		for (size_t i = 0; i < L; i++) {
			out << vec.data[i];
			if (i < L - 1) out << ", ";
		}
		out << "]";
		return out;
	}

#define PIRKK_VEC_ADD_OP(op) template<typename T, size_t L> Vec<T, L> operator##op
#define PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(op) PIRKK_VEC_ADD_OP(op) (const Vec<T, L> &a, const Vec<T, L> &b) { Vec<T, L> out; for (size_t i = 0; i < L; i++) out.data[i] = a.data[i] op b.data[i]; return out; }
#define PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(op) PIRKK_VEC_ADD_OP(op) (const Vec<T, L> &a, T b) { Vec<T, L> out; for (size_t i = 0; i < L; i++) out.data[i] = a.data[i] op b; return out; }
#define PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(op) PIRKK_VEC_ADD_OP(op) (T a, const Vec<T, L> &b) { Vec<T, L> out; for (size_t i = 0; i < L; i++) out.data[i] = a op b.data[i]; return out; }
#define PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(op) PIRKK_VEC_ADD_OP(op) (Vec<T, L> &a, const Vec<T, L> &b) { for (size_t i = 0; i < L; i++) a.data[i] op b.data[i]; return a; }
#define PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(op) PIRKK_VEC_ADD_OP(op) (Vec<T, L> &a, T b) { for (size_t i = 0; i < L; i++) a.data[i] op b; return a; }

	PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(+);
	PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(-);
	PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(*);
	PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(/ );
	PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(%);

	PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(+);
	PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(-);
	PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(*);
	PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(/ );
	PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(%);

	PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(+);
	PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(-);
	PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(*);
	PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(/ );
	PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(%);

	PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(+= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(-= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(*= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(/= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(%= );

	PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(+= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(-= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(*= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(/= );
	PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(%= );
}
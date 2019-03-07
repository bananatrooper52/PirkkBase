#pragma once

#include "..\vector\Vec.h"

namespace PirkkBase {
	template<typename T, size_t W, size_t H>
	struct Mat {
		Vec<T, H> data[W];

		Mat(T _v) { for (size_t x = 0; x < W; x++) for (size_t y = 0; y < H; y++) data[x][y] = x == y ? v : 0; }
		Mat() : Mat(1) {}
	};

	template<typename T, size_t W, size_t H>
	std::ostream &operator<<(std::ostream &out, const Mat<T, W, H> &mat) {
		out << "[";
		for (size_t x = 0; x < W; x++) {
			out << "[";
			for (size_t y = 0; y < W; y++) {
				out << mat.data[x][y];
				if (x < W - 1) out << ", ";
			}
			out << "]";
			if (y < H - 1) out << ", ";
		}
		out << "]";
		return out;
	}

#define PIRKK_MAT_ADD_OP(op) template<typename T, size_t W, size_t H> Mat<T, W, H> operator##op
#define PIRKK_MAT_ADD_OP_ARITH_VEC_VEC(op) PIRKK_VEC_ADD_OP(op) (const Mat<T, W, H> &a, const Mat<T, W, H> &b) { Mat<T, W, H> out; for (size_t i = 0; i < L; i++) out.data[i] = a.data[i] op b.data[i]; return out; }
#define PIRKK_MAT_ADD_OP_ARITH_VEC_SCALAR(op) PIRKK_VEC_ADD_OP(op) (const Mat<T, W, H> &a, T b) { Mat<T, W, H> out; for (size_t i = 0; i < L; i++) out.data[i] = a.data[i] op b; return out; }
#define PIRKK_MAT_ADD_OP_ARITH_SCALAR_VEC(op) PIRKK_VEC_ADD_OP(op) (T a, const Mat<T, W, H> &b) { Mat<T, W, H> out; for (size_t i = 0; i < L; i++) out.data[i] = a op b.data[i]; return out; }
#define PIRKK_MAT_ADD_OP_ASSIGN_VEC_VEC(op) PIRKK_VEC_ADD_OP(op) (Mat<T, W, H> &a, const Mat<T, W, H> &b) { for (size_t i = 0; i < L; i++) a.data[i] op b.data[i]; return a; }
#define PIRKK_MAT_ADD_OP_ASSIGN_VEC_SCALAR(op) PIRKK_VEC_ADD_OP(op) (Mat<T, W, H> &a, T b) { for (size_t i = 0; i < L; i++) a.data[i] op b; return a; }
}
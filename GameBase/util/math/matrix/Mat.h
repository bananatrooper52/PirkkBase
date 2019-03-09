#pragma once

#include "..\vector\Vec.h"
#include <iostream>

namespace PirkkBase {
	namespace Math {
		template<typename T, size_t W, size_t H>
		struct Mat {
			Vec<T, H> data[W]; // Columns

			// TODO: research initializer list
			Mat(T _data[W][H]) { std::copy(_data, _data + W * H, data); }
			Mat(Vec<T, H> _data[W]) { std::copy(_data, _data + W * H, data); }
			Mat(T _v) { for (size_t x = 0; x < W; x++) for (size_t y = 0; y < H; y++) data[x][y] = (x == y) ? _v : 0; }
			Mat() : Mat(1) {}
			Vec<T, H> &operator[](size_t i) { return data[i]; }
			Vec<T, H> operator[](size_t i) const { return data[i]; }

			void print() {
				for (size_t i = 0; i < W; i++) {
					std::cout << data[i] << "\n";
				}
			}
		};

		// Enable printing with std::cout
		template<typename T, size_t W, size_t H>
		std::ostream &operator<<(std::ostream &out, const Mat<T, W, H> &mat) {
			out << "[";
			for (size_t i = 0; i < W; i++) {
				out << mat[i];
				if (i < W - 1) out << ", ";
			}
			out << "]";
			return out;
		}

		// UNARY OPERATORS //

		// General unary
#define PIRKK_MAT_OP_UN(op)								\
template<typename T, size_t W, size_t H>				\
Mat<T, W, H> operator##op(const Mat<T, W, H> &a) {		\
	Mat<T, W, H> out;									\
	for (size_t i = 0; i < W; i++) out[i] = op a[i];	\
	return out;											\
}

		PIRKK_MAT_OP_UN(+);
		PIRKK_MAT_OP_UN(-);
		PIRKK_MAT_OP_UN(~);

		// Increment and decrement prefix
#define PIRKK_MAT_OP_INC_DEC_PREFIX(op)			\
template<typename T, size_t W, size_t H>		\
Mat<T, W, H> &operator##op(Mat<T, W, H> &a) {	\
	for (size_t i = 0; i < W; i++) op##a[i];	\
	return a;									\
}

		// Increment and decrement postfix
#define PIRKK_MAT_OP_INC_DEC_POSTFIX(op)				\
template<typename T, size_t W, size_t H>				\
Mat<T, W, H> operator##op(const Mat<T, W, H> &a, int) {	\
	Mat<T, W, H> out = a;								\
	for (size_t i = 0; i < W; i++) a[i]##op;			\
	return out;											\
}

	// Increment and decrement postfix and prefix
#define PIRKK_MAT_OP_INC_DEC(op) PIRKK_MAT_OP_INC_DEC_PREFIX(op) PIRKK_MAT_OP_INC_DEC_POSTFIX(op)

		PIRKK_MAT_OP_INC_DEC(++);
		PIRKK_MAT_OP_INC_DEC(--);

		// BINARY OPERATORS //

		// Mat op Mat
#define PIRKK_MAT_OP_BIN_MAT_MAT(op)											\
template<typename T, size_t W0, size_t H0, size_t W1, size_t H1>				\
Mat<T, W1, H0> operator##op(const Mat<T, W0, H0> &a, const Mat<T, W1, H1> &b) {	\
	/*static_assert(W0 == H1);*/												\
	Mat<T, W1, H0> out;															\
	for (size_t x = 0; x < W1; x++)												\
		for (size_t y = 0; y < H0; y++) {										\
			out[x][y] = 0;														\
			for (size_t i = 0; i < W0; i++)	out[x][y] += a[i][y] * b[x][i];		\
}																				\
	return out;																	\
}

		// Mat op Scalar
#define PIRKK_MAT_OP_BIN_MAT_SCALAR(op)						\
template<typename T, size_t W, size_t H>					\
Mat<T, W, H> operator##op(const Mat<T, W, H> &a, T b) {		\
	Mat<T, W, H> out;										\
	for (size_t i = 0; i < W; i++) out[i] = a[i] op b;		\
	return out;												\
}

		// Scalar op Mat
#define PIRKK_MAT_OP_BIN_SCALAR_MAT(op)						\
template<typename T, size_t W, size_t H>					\
Mat<T, W, H> operator##op(T a, const Mat<T, W, H> &b) {		\
	Mat<T, W, H> out;										\
	for (size_t i = 0; i < W; i++) out[i] = a op b[i];		\
	return out;												\
}

		// All binary functions
#define PIRKK_MAT_OP_BIN(op) PIRKK_MAT_OP_BIN_MAT_MAT(op) PIRKK_MAT_OP_BIN_MAT_SCALAR(op) PIRKK_MAT_OP_BIN_SCALAR_MAT(op)

		PIRKK_MAT_OP_BIN(+);
		PIRKK_MAT_OP_BIN(-);
		PIRKK_MAT_OP_BIN(*);
		PIRKK_MAT_OP_BIN(/ );
		PIRKK_MAT_OP_BIN(%);
		PIRKK_MAT_OP_BIN(&);
		PIRKK_MAT_OP_BIN(| );
		PIRKK_MAT_OP_BIN(<< );
		PIRKK_MAT_OP_BIN(>> );
		PIRKK_MAT_OP_BIN(^);

		// ASSIGNMENT OPERATORS //

		// Mat op Mat
#define PIRKK_MAT_OP_ASSIGN_MAT_MAT(op)									\
template<typename T, size_t W, size_t H>								\
Mat<T, W, H> operator##op##=(Mat<T, W, H> &a, const Mat<T, W, H> &b) {	\
	return a = a op b;													\
}

		// Mat op Scalar
#define PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(op)				\
template<typename T, size_t W, size_t H>				\
Mat<T, W, H> operator##op##=(Mat<T, W, H> &a, T b) {	\
	return a = a op b;									\
}

		// All assignment functions
#define PIRKK_MAT_OP_ASSIGN(op) PIRKK_MAT_OP_ASSIGN_MAT_MAT(op) PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(op)

		PIRKK_MAT_OP_ASSIGN(+);
		PIRKK_MAT_OP_ASSIGN(-);
		PIRKK_MAT_OP_ASSIGN(*);
		PIRKK_MAT_OP_ASSIGN(/ );
		PIRKK_MAT_OP_ASSIGN(%);
		PIRKK_MAT_OP_ASSIGN(&);
		PIRKK_MAT_OP_ASSIGN(| );
		PIRKK_MAT_OP_ASSIGN(<< );
		PIRKK_MAT_OP_ASSIGN(>> );
		PIRKK_MAT_OP_ASSIGN(^);

#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"

#define PIRKK_MAT_USING_ALL_TYPES(w, h)					\
template<typename T> using Mat##w##x##h = Mat<T, w, h>;	\
using Mat##w##x##h##ub = Mat##w##x##h##<uint8_t>;		\
using Mat##w##x##h##us = Mat##w##x##h##<uint16_t>;		\
using Mat##w##x##h##ui = Mat##w##x##h##<uint32_t>;		\
using Mat##w##x##h##ul = Mat##w##x##h##<uint64_t>;		\
using Mat##w##x##h##b = Mat##w##x##h##<int8_t>;			\
using Mat##w##x##h##s = Mat##w##x##h##<int16_t>;		\
using Mat##w##x##h##i = Mat##w##x##h##<int32_t>;		\
using Mat##w##x##h##l = Mat##w##x##h##<int64_t>;		\
using Mat##w##x##h##f = Mat##w##x##h##<float_t>;		\
using Mat##w##x##h##d = Mat##w##x##h##<double_t>

#define PIRKK_MAT_USING_ALL_TYPES_EVEN(len)				\
template<typename T> using Mat##len = Mat<T, len, len>;	\
using Mat##len##ub = Mat##len##<uint8_t>;				\
using Mat##len##us = Mat##len##<uint16_t>;				\
using Mat##len##ui = Mat##len##<uint32_t>;				\
using Mat##len##ul = Mat##len##<uint64_t>;				\
using Mat##len##b = Mat##len##<int8_t>;					\
using Mat##len##s = Mat##len##<int16_t>;				\
using Mat##len##i = Mat##len##<int32_t>;				\
using Mat##len##l = Mat##len##<int64_t>;				\
using Mat##len##f = Mat##len##<float_t>;				\
using Mat##len##d = Mat##len##<double_t>

		PIRKK_MAT_USING_ALL_TYPES_EVEN(2);
		PIRKK_MAT_USING_ALL_TYPES(2, 3);
		PIRKK_MAT_USING_ALL_TYPES(2, 4);
		PIRKK_MAT_USING_ALL_TYPES(3, 2);
		PIRKK_MAT_USING_ALL_TYPES_EVEN(3);
		PIRKK_MAT_USING_ALL_TYPES(3, 4);
		PIRKK_MAT_USING_ALL_TYPES(4, 2);
		PIRKK_MAT_USING_ALL_TYPES(4, 3);
		PIRKK_MAT_USING_ALL_TYPES_EVEN(4);
	}
}
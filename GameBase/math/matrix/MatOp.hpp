#pragma once

#include "Mat.hpp"

namespace pirkk::math {
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

	// Mat op Mat Multiplication
#define PIRKK_MAT_OP_BIN_MAT_MAT_MUL(op)										\
template<typename T, size_t W0, size_t H0, size_t W1>							\
Mat<T, W1, H0> operator##op(const Mat<T, W0, H0> &a, const Mat<T, W1, W0> &b) {	\
	Mat<T, W1, H0> out = Mat<T, W1, H0>::zero();								\
	for (size_t x = 0; x < W1; x++)												\
		for (size_t y = 0; y < H0; y++)											\
			for (size_t i = 0; i < W0; i++)	out[x][y] += a[i][y] op b[x][i];	\
	return out;																	\
}

	PIRKK_MAT_OP_BIN_MAT_MAT_MUL(*);

#define PIRKK_MAT_OP_BIN_MAT_MAT_ADD_SUB(op)														\
template<typename T, size_t W, size_t H>															\
Mat<T, W, H> operator##op(const Mat<T, W, H> &a, const Mat<T, W, H> &b) {							\
	Mat<T, W, H> out;																				\
	for (size_t x = 0; x < W; x++) for (size_t y = 0; y < H; y++) out[x][y] = a[x][y] op b[x][y];	\
	return out;																						\
}

	PIRKK_MAT_OP_BIN_MAT_MAT_ADD_SUB(+);
	PIRKK_MAT_OP_BIN_MAT_MAT_ADD_SUB(-);

	// Mat op Vec Multiplication
#define PIRKK_MAT_OP_BIN_MAT_VEC_MUL(op)							\
template<typename T, size_t W, size_t H>							\
Vec<T, H> operator*(const Mat<T, W, H> &a, const Vec<T, W> &b) { 	\
	Vec<T, W> initializer[1] = { b };								\
	Mat<T, 1, W> bMat = Mat<T, 1, W>(initializer);					\
	Mat<T, 1, H> out = a * bMat;									\
	return out[0];													\
}

	PIRKK_MAT_OP_BIN_MAT_VEC_MUL(*);

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
#define PIRKK_MAT_OP_BIN(op) PIRKK_MAT_OP_BIN_MAT_SCALAR(op) PIRKK_MAT_OP_BIN_SCALAR_MAT(op)

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

	// Mat op Scalar
#define PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(op)				\
template<typename T, size_t W, size_t H>				\
Mat<T, W, H> operator##op##=(Mat<T, W, H> &a, T b) {	\
	return a = a op b;									\
}

	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(+);
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(-);
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(*);
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(/ );
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(%);
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(&);
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(| );
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(<< );
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(>> );
	PIRKK_MAT_OP_ASSIGN_MAT_SCALAR(^);

	// Mat op Mat
#define PIRKK_MAT_OP_ASSIGN_MAT_MAT(op)									\
template<typename T, size_t W, size_t H>								\
Mat<T, W, H> operator##op##=(Mat<T, W, H> &a, const Mat<T, W, H> &b) {	\
	return a = a op b;													\
}
	PIRKK_MAT_OP_ASSIGN_MAT_MAT(+);
	PIRKK_MAT_OP_ASSIGN_MAT_MAT(-);
}
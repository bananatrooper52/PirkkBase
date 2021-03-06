#pragma once

#include "Vec.hpp"

namespace pirkk::math {

	// UNARY OPERATORS //

	// General unary
#define PIRKK_VEC_OP_UN(op)								\
template<typename T, size_t L>							\
Vec<T, L> operator##op(const Vec<T, L>& a) {			\
	Vec<T, L> out;										\
	for (size_t i = 0; i < L; i++) out[i] = op a[i];	\
	return out;											\
}

	PIRKK_VEC_OP_UN(+);
	PIRKK_VEC_OP_UN(-);
	PIRKK_VEC_OP_UN(~);

	// Increment and decrement prefix
#define PIRKK_VEC_OP_INC_DEC_PREFIX(op)			\
template<typename T, size_t L>					\
Vec<T, L>& operator##op(Vec<T, L>& a) {			\
	for (size_t i = 0; i < L; i++) op##a[i];	\
	return a;									\
}

		// Increment and decrement postfix
#define PIRKK_VEC_OP_INC_DEC_POSTFIX(op)		\
template<typename T, size_t L>					\
Vec<T, L> operator##op(Vec<T, L>& a, int) {		\
	Vec<T, L> out = a;							\
	for (size_t i = 0; i < L; i++) a[i]##op;	\
	return out;									\
}

		// Increment and decrement postfix and prefix
#define PIRKK_VEC_OP_INC_DEC(op) PIRKK_VEC_OP_INC_DEC_PREFIX(op) PIRKK_VEC_OP_INC_DEC_POSTFIX(op)

	PIRKK_VEC_OP_INC_DEC(++);
	PIRKK_VEC_OP_INC_DEC(--);

	// BINARY OPERATORS //

	// Vec op Vec
#define PIRKK_VEC_OP_BIN_VEC_VEC(op)								\
template<typename T, size_t L>										\
Vec<T, L> operator##op(const Vec<T, L>& a, const Vec<T, L>& b) {	\
	Vec<T, L> out;													\
	for (size_t i = 0; i < L; i++) out[i] = a[i] op b[i];			\
	return out;														\
}

		// Vec op Scalar
#define PIRKK_VEC_OP_BIN_VEC_SCALAR(op)					\
template<typename T, size_t L>							\
Vec<T, L> operator##op(const Vec<T, L>& a, T b) {		\
	Vec<T, L> out;										\
	for (size_t i = 0; i < L; i++) out[i] = a[i] op b;	\
	return out;											\
}

		// Scalar op Vec
#define PIRKK_VEC_OP_BIN_SCALAR_VEC(op)					\
template<typename T, size_t L>							\
Vec<T, L> operator##op(T a, const Vec<T, L>& b) {		\
	Vec<T, L> out;										\
	for (size_t i = 0; i < L; i++) out[i] = a op b[i];	\
	return out;											\
}

		// All binary functions
#define PIRKK_VEC_OP_BIN(op) PIRKK_VEC_OP_BIN_VEC_VEC(op) PIRKK_VEC_OP_BIN_VEC_SCALAR(op) PIRKK_VEC_OP_BIN_SCALAR_VEC(op)

	PIRKK_VEC_OP_BIN(+);
	PIRKK_VEC_OP_BIN(-);
	PIRKK_VEC_OP_BIN(*);
	PIRKK_VEC_OP_BIN(/ );
	PIRKK_VEC_OP_BIN(%);
	PIRKK_VEC_OP_BIN(&);
	PIRKK_VEC_OP_BIN(| );
	PIRKK_VEC_OP_BIN(<< );
	PIRKK_VEC_OP_BIN(>> );
	PIRKK_VEC_OP_BIN(^);

	// ASSIGNMENT OPERATORS //

	// Vec op Vec
#define PIRKK_VEC_OP_ASSIGN_VEC_VEC(op)							\
template<typename T, size_t L>									\
Vec<T, L> operator##op##=(Vec<T, L>& a, const Vec<T, L>& b) {	\
	a = a op b;													\
	return a;													\
}

		// Vec op Scalar
#define PIRKK_VEC_OP_ASSIGN_VEC_SCALAR(op)		\
template<typename T, size_t L>					\
Vec<T, L> operator##op##=(Vec<T, L>& a, T b) {	\
	a = a op b;									\
	return a;									\
}

		// All assignment functions
#define PIRKK_VEC_OP_ASSIGN(op) PIRKK_VEC_OP_ASSIGN_VEC_VEC(op) PIRKK_VEC_OP_ASSIGN_VEC_SCALAR(op)

	PIRKK_VEC_OP_ASSIGN(+);
	PIRKK_VEC_OP_ASSIGN(-);
	PIRKK_VEC_OP_ASSIGN(*);
	PIRKK_VEC_OP_ASSIGN(/ );
	PIRKK_VEC_OP_ASSIGN(%);
	PIRKK_VEC_OP_ASSIGN(&);
	PIRKK_VEC_OP_ASSIGN(| );
	PIRKK_VEC_OP_ASSIGN(<< );
	PIRKK_VEC_OP_ASSIGN(>> );
	PIRKK_VEC_OP_ASSIGN(^);

	// TODO: 1D vector (simulated scalar) implicit conversions
}
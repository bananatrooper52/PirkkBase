#pragma once

#include "Vec.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace PirkkBase {
#define PIRKK_VEC_ADD_OP_ARITH_VEC_VEC(op) template<typename T, size_t L> Vec<T, L> operator##op (const Vec<T, L> &a, const Vec<T, L> &b) { Vec<T, L> out; for (size_t i = 0; i < L; i++) out.data[i] = a.data[i] op b.data[i]; return out; }
#define PIRKK_VEC_ADD_OP_ARITH_VEC_SCALAR(op) template<typename T, size_t L> Vec<T, L> operator##op (const Vec<T, L> &a, T b) { Vec<T, L> out; for (size_t i = 0; i < L; i++) out.data[i] = a.data[i] op b; return out; }
#define PIRKK_VEC_ADD_OP_ARITH_SCALAR_VEC(op) template<typename T, size_t L> Vec<T, L> operator##op (T a, const Vec<T, L> &b) { Vec<T, L> out; for (size_t i = 0; i < L; i++) out.data[i] = a op b.data[i]; return out; }
#define PIRKK_VEC_ADD_OP_ASSIGN_VEC_VEC(op) template<typename T, size_t L> Vec<T, L> operator##op (Vec<T, L> &a, const Vec<T, L> &b) { for (size_t i = 0; i < L; i++) a.data[i] op b.data[i]; return a; }
#define PIRKK_VEC_ADD_OP_ASSIGN_VEC_SCALAR(op) template<typename T, size_t L> Vec<T, L> operator##op (Vec<T, L> &a, T b) { for (size_t i = 0; i < L; i++) a.data[i] op b; return a; }

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

	// Dot product of two vectors
	template<typename T, size_t L>
	T dot(Vec<T, L> a, Vec<T, L> b) {
		T out = 0;
		for (size_t i = 0; i < L; i++) {
			out += a[i] * b[i];
		}
		return out;
	}

	// Squared magnitude of a vector
	// Use when possible to avoid square root operation
	template<typename T, size_t L>
	T mag2(Vec<T, L> v) {
		return dot(v, v);
	}

	// Magnitude of a vector
	template<typename T, size_t L>
	T mag(Vec<T, L> v) {
		return sqrt(mag2(v));
	}

	// Just for convenience, same as dot product
	template<typename T, size_t L>
	T distance2(Vec<T, L> a, Vec<T, L> b) {
		return dot(a, b);
	}

	// Distance between two vectors
	template<typename T, size_t L>
	T distance(Vec<T, L> a, Vec<T, L> b) {
		return sqrt(dot(a, b));
	}

	// Cross product of two 3 dimensional vectors
	template<typename T>
	Vec<T, 3> cross(Vec<T, 3> a, Vec<T, 3> b) {
		return Vec<T, 3>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
			);
	}

	template<typename T> using Vec2 = Vec<T, 2>;
	template<typename T> using Vec3 = Vec<T, 3>;
	template<typename T> using Vec4 = Vec<T, 4>;

	using Vec2ub = Vec2<uint8_t>;
	using Vec2us = Vec2<uint16_t>;
	using Vec2ui = Vec2<uint32_t>;
	using Vec2ul = Vec2<uint64_t>;

	using Vec2b = Vec2<int8_t>;
	using Vec2s = Vec2<int16_t>;
	using Vec2i = Vec2<int32_t>;
	using Vec2l = Vec2<int64_t>;
	using Vec2f = Vec2<float_t>;
	using Vec2d = Vec2<double_t>;

	using Vec3ub = Vec3<uint8_t>;
	using Vec3us = Vec3<uint16_t>;
	using Vec3ui = Vec3<uint32_t>;
	using Vec3ul = Vec3<uint64_t>;

	using Vec3b = Vec3<int8_t>;
	using Vec3s = Vec3<int16_t>;
	using Vec3i = Vec3<int32_t>;
	using Vec3l = Vec3<int64_t>;
	using Vec3f = Vec3<float_t>;
	using Vec3d = Vec3<double_t>;

	using Vec4ub = Vec4<uint8_t>;
	using Vec4us = Vec4<uint16_t>;
	using Vec4ui = Vec4<uint32_t>;
	using Vec4ul = Vec4<uint64_t>;

	using Vec4b = Vec4<int8_t>;
	using Vec4s = Vec4<int16_t>;
	using Vec4i = Vec4<int32_t>;
	using Vec4l = Vec4<int64_t>;
	using Vec4f = Vec2<float_t>;
	using Vec4d = Vec2<double_t>;
}
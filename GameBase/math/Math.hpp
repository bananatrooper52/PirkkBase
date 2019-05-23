#pragma once

#include "vector/Vec.hpp"
#include "matrix/Mat.hpp"
#include "quaternion/Quat.hpp"

namespace pirkk::math {

	template<typename T>
	T pi() {
		return (T)3.14159265358979323846;
	}

	// Linear interpolate a value (scalar or vector)
	template<typename T, typename U>
	T lerp(T a, T b, U t) {
		return a + (b - a) * t;
	}

	template<typename T>
	T abs(T & a) {
		return a >= 0 ? a : -a;
	}

	template<typename T, size_t L>
	T abs(const Vec<T, L> & a) {
		Vec<T, L> out;
		for (size_t i = 0; i < L; i++) {
			out[i] = abs(a[i]);
		}
	}

	// Dot product of two vectors
	template<typename T, size_t L>
	T dot(const Vec<T, L> & a, const Vec<T, L> & b) {
		T out = 0;
		for (size_t i = 0; i < L; i++) {
			out += a[i] * b[i];
		}
		return out;
	}

	template<typename T>
	T dot(const Quat<T> & a, const Quat<T> & b) {
		return a.w* b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	}

	// Squared magnitude of a vector
	// Use when possible to avoid square root operation
	template<typename T, size_t L>
	T mag2(const Vec<T, L> & v) {
		return dot(v, v);
	}

	template<typename T>
	T mag2(const Quat<T> & v) {
		return dot(v, v);
	}

	// Magnitude of a vector
	template<typename T, size_t L>
	T mag(const Vec<T, L> & v) {
		return sqrt(mag2(v));
	}

	template<typename T>
	T mag(const Quat<T> & v) {
		return sqrt(mag2(v));
	}

	// Squared distance between two vectors
	template<typename T, size_t L>
	T distance2(const Vec<T, L> & a, const Vec<T, L> & b) {
		return abs(dot(a - b, a - b));
	}

	// Distance between two vectors
	template<typename T, size_t L>
	T distance(const Vec<T, L> & a, const Vec<T, L> & b) {
		return sqrt(distance2(a, b));
	}

	// Normalize vector
	template<typename T, size_t L>
	Vec<T, L> normalize(const Vec<T, L> & v) {
		return v / mag(v);
	}

	template<typename T>
	Quat<T> normalize(const Quat<T> & v) {
		float m = mag(v);
		return Quat(
			v.w / m,
			v.x / m,
			v.y / m,
			v.z / m
		);
	}

	// Cross product of two 3 dimensional vectors
	template<typename T>
	Vec3<T> cross(const Vec3<T> & a, const Vec3<T> & b) {
		return Vec3<T>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
			);
	}

	// Get the linear index of a vector position within a space
	template<typename T, size_t L>
	T linearIndex(Vec<T, L> pos, Vec<T, L> bounds) {
		T index = 0;
		for (size_t i = 0; i < L; i++) {
			T div = 0;
			for (size_t j = 0; j < i; j++) {
				div += bounds[j];
			}
			index += pos[i] / div == 0 ? 1 : div;
		}
		return index;
	}

	// Create a translation matrix
	template<typename T, size_t L>
	Mat<T, L + 1, L + 1> translate(const Vec<T, L> & translation) {
		Mat<T, L + 1, L + 1> out;
		for (size_t i = 0; i < L; i++) {
			out[L][i] += translation[i];
		}
		return out;
	}

	// Create a scale matrix
	template<typename T, size_t L>
	Mat<T, L + 1, L + 1> scale(const Vec<T, L> & scale) {
		Mat<T, L + 1, L + 1> out;
		for (size_t i = 0; i < L; i++) {
			out[i][i] *= scale[i];
		}
		return out;
	}

	// Create a rotation matrix
	template<typename T>
	Mat4<T> rotate(const Vec3<T> & axis, T angle) {
		T a = angle;
		T c = cos(a);
		T s = sin(a);
		T t = 1 - c;

		Vec3<T> ax = normalize(axis);

		T x = ax.x;
		T y = ax.y;
		T z = ax.z;

		T v1r1 = x * y * t;
		T v2r1 = z * s;

		T v1r2 = x * z * t;
		T v2r2 = y * s;

		T v1r3 = y * z * t;
		T v2r3 = x * s;

		T matVals[] = {
			c + x * x * t, v1r1 + v2r1, v1r2 - v2r2, 0,
			v1r1 - v2r1, c + y * y * t, v1r3 + v2r3, 0,
			v1r2 + v2r2, v1r3 - v2r3, c + z * z * t, 0,
			0, 0, 0, 1
		};

		return Mat4<T>(matVals);
	}

	// TODO: shear matrix
}
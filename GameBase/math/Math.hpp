#pragma once

#include "vector/Vec.hpp"
#include "matrix/Mat.hpp"

namespace Pirkk::Math {

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
	T abs(T &a) {
		return a >= 0 ? a : -a;
	}

	template<typename T, size_t L>
	T abs(const Vec<T, L> &a) {
		Vec<T, L> out;
		for (size_t i = 0; i < L; i++) {
			out[i] = abs(a[i]);
		}
	}

	// Dot product of two vectors
	template<typename T, size_t L>
	T dot(const Vec<T, L> &a, const Vec<T, L> &b) {
		T out = 0;
		for (size_t i = 0; i < L; i++) {
			out += a[i] * b[i];
		}
		return out;
	}

	// Squared magnitude of a vector
	// Use when possible to avoid square root operation
	template<typename T, size_t L>
	T mag2(const Vec<T, L> &v) {
		return dot(v, v);
	}

	// Magnitude of a vector
	template<typename T, size_t L>
	T mag(const Vec<T, L> &v) {
		return sqrt(mag2(v));
	}

	// Squared distance between two vectors
	template<typename T, size_t L>
	T distance2(const Vec<T, L> &a, const Vec<T, L> &b) {
		return abs(dot(a - b, a - b));
	}

	// Distance between two vectors
	template<typename T, size_t L>
	T distance(const Vec<T, L> &a, const Vec<T, L> &b) {
		return sqrt(distance2(a, b));
	}

	// Normalize vector
	template<typename T, size_t L>
	Vec<T, L> normalize(const Vec<T, L> &v) {
		return v / mag(v);
	}

	// Cross product of two 3 dimensional vectors
	template<typename T>
	Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b) {
		return Vec3<T>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
			);
	}

	// Create a translation matrix
	template<typename T, size_t L>
	Mat<T, L + 1, L + 1> translate(const Vec<T, L> &translation) {
		Mat<T, L + 1, L + 1> out;
		for (size_t i = 0; i < L; i++) {
			out[L][i] += translation[i];
		}
		return out;
	}

	// Create a scale matrix
	template<typename T, size_t L>
	Mat<T, L + 1, L + 1> scale(const Vec<T, L> &scale) {
		Mat<T, L + 1, L + 1> out;
		for (size_t i = 0; i < L; i++) {
			out[i][i] *= scale[i];
		}
		return out;
	}

	// Create a rotation matrix
	template<typename T>
	Mat4<T> rotate(const Vec3<T> &axis, T angle) {
		T a = angle;
		T c = cos(a);
		T s = sin(a);
		Vec3<T> ax = normalize(axis);
		Vec3<T> t((T(1) - c) * ax);

		T matVals[] = {
			c + ax.x + t.x, t.x * ax.y + s * ax.z, t.x * ax.z - s * ax.y, 0,
			t.y * ax.x - s * ax.z, c + t.y * ax.y, t.y * ax.z + s * ax.x, 0,
			t.z * ax.x + s * ax.y, t.z * ax.y - s * ax.x, c + t.z * ax.z, 0,
			0, 0, 0, 1
		};

		return Mat4<T>(matVals);
	}

	// TODO: quaternions
	// TODO: rotation matrix
	// TODO: shear matrix
}
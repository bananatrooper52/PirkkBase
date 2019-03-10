#pragma once

#include "vector/Vec.h"
#include "matrix/Mat.h"

namespace PirkkBase {
	namespace Math {

		// Linear interpolate a value (scalar or vector)
		template<typename T, typename U>
		T lerp(T a, T b, U t) {
			return a + (b - a) * t;
		}

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
		Vec3<T> cross(Vec3<T> a, Vec3<T> b) {
			return Vec3<T>(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
				);
		}

		// Create a translation matrix
		template<typename T, size_t L>
		Mat<T, L + 1, L + 1> translate(const Mat<T, L + 1, L + 1> &mat, const Vec<T, L> &translation) {
			Mat<T, L + 1, L + 1> out = mat;
			for (size_t i = 0; i < L; i++) {
				out[L][i] += translation[i];
			}
			return out;
		}
		
		// Create a scale matrix
		template<typename T, size_t L>
		Mat<T, L + 1, L + 1> scale(const Mat<T, L + 1, L + 1> &mat, const Vec<T, L> &scale) {
			Mat<T, L + 1, L + 1> out = mat;
			for (size_t i = 0; i < L; i++) {
				out[i][i] *= scale[i];
			}
			return out;
		}

		// TODO: quaternions
		// TODO: rotation matrix
		// TODO: shear matrix
	}
}
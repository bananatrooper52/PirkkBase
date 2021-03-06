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
	T lerp(const T& a, const T& b, const U& t) {
		return a + (b - a) * t;
	}

	template<typename T>
	T abs(const T& a) {
		return a >= 0 ? a : -a;
	}

	template<typename T, size_t L>
	T abs(const Vec<T, L>& a) {
		Vec<T, L> out;
		for (size_t i = 0; i < L; i++) {
			out[i] = abs(a[i]);
		}
	}

	// Dot product of two vectors
	template<typename T, size_t L>
	T dot(const Vec<T, L>& a, const Vec<T, L>& b) {
		T out = 0;
		for (size_t i = 0; i < L; i++) {
			out += a[i] * b[i];
		}
		return out;
	}

	template<typename T>
	T dot(const Quat<T>& a, const Quat<T>& b) {
		return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	}

	// Squared magnitude of a vector
	// Use when possible to avoid square root operation
	template<typename T, size_t L>
	T mag2(const Vec<T, L>& v) {
		return dot(v, v);
	}

	template<typename T>
	T mag2(const Quat<T>& v) {
		return dot(v, v);
	}

	// Magnitude of a vector
	template<typename T, size_t L>
	T mag(const Vec<T, L>& v) {
		return sqrt(mag2(v));
	}

	template<typename T>
	T mag(const Quat<T>& v) {
		return sqrt(mag2(v));
	}

	// Squared distance between two vectors
	template<typename T, size_t L>
	T distance2(const Vec<T, L>& a, const Vec<T, L>& b) {
		return abs(dot(a - b, a - b));
	}

	// Distance between two vectors
	template<typename T, size_t L>
	T distance(const Vec<T, L>& a, const Vec<T, L>& b) {
		return sqrt(distance2(a, b));
	}

	// Normalize vector
	template<typename T, size_t L>
	Vec<T, L> normalize(const Vec<T, L>& v) {
		return v / mag(v);
	}

	template<typename T>
	Quat<T> normalize(const Quat<T>& v) {
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
	Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b) {
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
			index += pos[i] / ((div == 0) ? 1 : div);
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
	Mat4<T> rotate(const Vec3<T>& axis, const T& angle) {
		T a = angle;
		T c = cos(a);
		T s = sin(a);

		Vec3<T> ax = normalize(axis);
		Vec3<T> tmp((T(1) - c) * ax);

		Mat4<T> r;

		r[0][0] = c + tmp[0] * ax[0];
		r[0][1] = tmp[0] * ax[1] + s * ax[2];
		r[0][2] = tmp[0] * ax[2] - s * ax[1];

		r[1][0] = tmp[1] * ax[0] - s * ax[2];
		r[1][1] = c + tmp[1] * ax[1];
		r[1][2] = tmp[1] * ax[2] + s * axis[0];

		r[2][0] = tmp[2] * axis[0] + s * ax[1];
		r[2][1] = tmp[2] * axis[1] - s * ax[0];
		r[2][2] = c + tmp[2] * ax[2];

		Mat4<T> m(1);
		Mat4<T> out;
		out[0] = m[0] * r[0][0] + m[1] * r[0][1] + m[2] * r[0][2];
		out[1] = m[0] * r[1][0] + m[1] * r[1][1] + m[2] * r[1][2];
		out[2] = m[0] * r[2][0] + m[1] * r[2][1] + m[2] * r[2][2];

		return out;
	}

	// Create a quaternion from axis and angle
	template<typename T>
	Quat<T> axisAngle(const Vec3<T>& axis, const T& angle) {
		Quat<T> q;

		T s = sin(angle * T(0.5));

		q.w = cos(angle * T(0.5));
		q.x = axis.x * s;
		q.y = axis.y * s;
		q.z = axis.z * s;

		return q;
	}

	template<typename T>
	Mat4<T> toMatrix(Quat<T> q) {
		Mat4<T> m;

		T qxx(q.x * q.x);
		T qyy(q.y * q.y);
		T qzz(q.z * q.z);
		T qxz(q.x * q.z);
		T qxy(q.x * q.y);
		T qyz(q.y * q.z);
		T qwx(q.w * q.x);
		T qwy(q.w * q.y);
		T qwz(q.w * q.z);

		m[0][0] = T(1) - T(2) * (qyy + qzz);
		m[0][1] = T(2) * (qxy + qwz);
		m[0][2] = T(2) * (qxz - qwy);

		m[1][0] = T(2) * (qxy - qwz);
		m[1][1] = T(1) - T(2) * (qxx + qzz);
		m[1][2] = T(2) * (qyz + qwx);

		m[2][0] = T(2) * (qxz + qwy);
		m[2][1] = T(2) * (qyz - qwx);
		m[2][2] = T(1) - T(2) * (qxx + qyy);

		return m;
	}

	// TODO: shear matrix
}
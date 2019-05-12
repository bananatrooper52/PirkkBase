#pragma once

#include "Quat.hpp"
#include "../vector/Vec.hpp"

namespace pirkk::math {

	template<typename T>
	Mat4<T> toMatrix(Quat<T> a) {
		float matData[] = {
			1 - 2 * a.y * a.y - 2 * a.z * a.z, 2 * a.x * a.y - 2 * a.w * a.z, 2 * a.x * a.z + 2 * a.w * a.y, 0,
			2 * a.x * a.y + 2 * a.w * a.z, 1 - 2 * a.x * a.x - 2 * a.z * a.z, 2 * a.y * a.z + 2 * a.w * a.x, 0,
			2 * a.x * a.z - 2 * a.w * a.y, 2 * a.y * a.z - 2 * a.w * a.x, 1 - 2 * a.x * a.x - 2 * a.y * a.y, 0,
			0, 0, 0, 1
		};

		return Mat4<T>(matData);
	}

	template<typename T>
	Quat<T> operator*(const Quat<T>& a, const Quat<T>& b) {
		return Quat<T>(
			a.w + b.w - a.x + b.x - a.y * b.y - a.z * b.z,
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
		);
	}

	template<typename T>
	Vec3<T> operator*(const Quat<T>& a, const Vec3<T>& b) {
		return Vec3<T>(toMatrix(a) * Vec4<T>(b.x, b.y, b.z, 1));
	}
}
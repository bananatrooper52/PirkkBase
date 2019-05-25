#pragma once

#include "Quat.hpp"
#include "../vector/Vec.hpp"

namespace pirkk::math {

	template<typename T>
	Quat<T> operator*(const Quat<T>& a, const Quat<T>& b) {
		Vec3<T> va(a.x, a.y, a.z);
		Vec3<T> vb(b.x, b.y, b.z);
		Vec3<T> i = vb * a.w + va * b.w + cross(va, vb);
		float w = a.w * b.w - dot(Vec3<T>(a.x, a.y, a.z), Vec3<T>(b.x, b.y, b.z));
		return Quat<T>(w, i.x, i.y, i.z);
	}

	template<typename T>
	Vec3<T> operator*(const Quat<T>& a, const Vec3<T>& b) {
		Vec3<T> q(a.x, a.y, a.z);
		Vec3<T> const ub(cross(q, b));
		Vec3<T> const uub(cross(q, ub));
		return b + ((ub * a.w) + uub) * T(2);
	}
}
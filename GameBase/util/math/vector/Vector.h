#pragma once

#include <ostream>
#include <cstdarg>
#include <cstdint>

#define FOR_EACH_COMP() for(size_t i = 0; i < L; i++)

namespace PirkkBase {
	template<typename T, size_t L>
	class Vector {
	protected:
		// Vector components
		T comp[L];

	public:

		Vector() {
			FOR_EACH_COMP() {
				comp[i] = 0;
			}
		}

		T &operator[](size_t i) {
			return comp[i];
		}

		template<typename T, size_t L>
		friend std::ostream &operator<<(std::ostream &out, const Vector<T, L> &v) {

			out << "(";

			FOR_EACH_COMP() {
				out << v.comp[i];
				if (i < L - 1) out << ", ";
			}

			out << ")";

			return out;
		}

		// Unary operators
#define UN_OP(op) Vector<T, L> operator##op() { Vector<T, L> v; FOR_EACH_COMP() v.comp[i] = op comp[i]; return v; }

		UN_OP(+);
		UN_OP(-);

#undef UN_OP

		// Binary operators VEC <-> SCALAR
#define ARITH_VEC_SCALAR(op, a, b, v) Vector<T, L> v; FOR_EACH_COMP() v.comp[i] = a.comp[i] op b; return v;
#define ARITH_VEC_SCALAR_OP(op) friend Vector<T, L> operator##op(Vector<T, L> a, T b) { ARITH_VEC_SCALAR(op, a, b, v); }
#define ARITH_SCALAR_VEC_OP(op) friend Vector<T, L> operator##op(T a, Vector<T, L> b) { ARITH_VEC_SCALAR(op, b, a, v); }
#define ARITH_VEC_SCALAR_BOTH_OP(op) ARITH_VEC_SCALAR_OP(op) ARITH_SCALAR_VEC_OP(op)

		ARITH_VEC_SCALAR_BOTH_OP(+);
		ARITH_VEC_SCALAR_BOTH_OP(-);
		ARITH_VEC_SCALAR_BOTH_OP(*);
		ARITH_VEC_SCALAR_BOTH_OP(/ );

#undef ARITH_VEC_SCALAR
#undef ARITH_VEC_SCALAR_OP
#undef ARITH_SCALAR_VEC_OP
#undef ARITH_VEC_SCALAR_BOTH_OP

		// Binary operators VEC <-> VEC
#define ARITH_VEC_VEC(op, a, b, v) Vector<T, L> v; FOR_EACH_COMP() v.comp[i] = a.comp[i] op b.comp[i]; return v;
#define ARITH_VEC_VEC_OP(op) friend Vector<T, L> operator##op(Vector<T, L> a, Vector<T, L> b) { ARITH_VEC_VEC(op, a, b, v); }

		ARITH_VEC_VEC_OP(+);
		ARITH_VEC_VEC_OP(-);
		ARITH_VEC_VEC_OP(*);
		ARITH_VEC_VEC_OP(/ );

#undef ARITH_VEC_VEC
#undef ARITH_VEC_VEC_OP

		template<typename T, typename U>
		static T dot(Vector<T, L> a, Vector<U, L> b) {
			float d = 0;
			FOR_EACH_COMP() {
				d += a[i] * b[i];
			}
			return d;
		}

		template<typename T, typename U>
		static T length(Vector<T, L> a, Vector<U, L> b) {
			return sqrt(dot(a, b));
		}

		T magSq() {
			dot(*this, *this);
		}

		T mag() {
			return sqrt(magSq());
		}

		T normalize() {
			return *this / magSq;
		}
	};

	template<typename T>
	class Vector1 : public Vector<T, 1> {
	public:

		T &x = Vector<T, 1>::comp[0];

		Vector1<T>() : Vector<T, 1>() {}

		Vector1<T>(T _x) {
			x = _x;
		}
	};

	template<typename T>
	class Vector2 : public Vector<T, 2> {
	public: 

		T &x = Vector<T, 2>::comp[0];
		T &y = Vector<T, 2>::comp[1];

		Vector2<T>(T _v) {
			x = _v;
			y = _v;
		}

		Vector2<T>(T _x, T _y) {
			x = _x;
			y = _y;
		}
	};

	template<typename T>
	class Vector3 : public Vector<T, 3> {
	public:

		T &x = Vector<T, 3>::comp[0];
		T &y = Vector<T, 3>::comp[1];
		T &z = Vector<T, 3>::comp[2];

		Vector3<T>(T _v) {
			x = _v;
			y = _v;
			z = _v;
		}

		Vector3<T>(T _x, T _y, T _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		// TODO: add cross product
	};

	template<typename T>
	class Vector4 : public Vector<T, 4> {
	public:

		T &x = Vector<T, 4>::comp[0];
		T &y = Vector<T, 4>::comp[1];
		T &z = Vector<T, 4>::comp[2];
		T &w = Vector<T, 4>::comp[3];

		Vector4<T>(T _v) {
			x = _v;
			y = _v;
			z = _v;
			w = _v;
		}

		Vector4<T>(T _x, T _y, T _z, T _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
	};

	typedef Vector1<uint8_t> ubVector1;
	typedef Vector2<uint8_t> ubVector2;
	typedef Vector3<uint8_t> ubVector3;
	typedef Vector4<uint8_t> ubVector4;

	typedef Vector1<int8_t> bVector1;
	typedef Vector2<int8_t> bVector2;
	typedef Vector3<int8_t> bVector3;
	typedef Vector4<int8_t> bVector4;

	typedef Vector1<uint16_t> usVector1;
	typedef Vector2<uint16_t> usVector2;
	typedef Vector3<uint16_t> usVector3;
	typedef Vector4<uint16_t> usVector4;

	typedef Vector1<int16_t> sVector1;
	typedef Vector2<int16_t> sVector2;
	typedef Vector3<int16_t> sVector3;
	typedef Vector4<int16_t> sVector4;

	typedef Vector1<uint32_t> uiVector1;
	typedef Vector2<uint32_t> uiVector2;
	typedef Vector3<uint32_t> uiVector3;
	typedef Vector4<uint32_t> uiVector4;

	typedef Vector1<int32_t> iVector1;
	typedef Vector2<int32_t> iVector2;
	typedef Vector3<int32_t> iVector3;
	typedef Vector4<int32_t> iVector4;

	typedef Vector1<uint64_t> ulVector1;
	typedef Vector2<uint64_t> ulVector2;
	typedef Vector3<uint64_t> ulVector3;
	typedef Vector4<uint64_t> ulVector4;

	typedef Vector1<int64_t> lVector1;
	typedef Vector2<int64_t> lVector2;
	typedef Vector3<int64_t> lVector3;
	typedef Vector4<int64_t> lVector4;

	typedef Vector1<float_t> fVector1;
	typedef Vector2<float_t> fVector2;
	typedef Vector3<float_t> fVector3;
	typedef Vector4<float_t> fVector4;

	typedef Vector1<double_t> dVector1;
	typedef Vector2<double_t> dVector2;
	typedef Vector3<double_t> dVector3;
	typedef Vector4<double_t> dVector4;
}

#undef FOR_EACH_COMP

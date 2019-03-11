#pragma once

#include "Mat.h"

namespace PirkkBase {
	namespace Math {

#define PIRKK_MAT_USING_ALL_TYPES(w, h)					\
template<typename T> using Mat##w##x##h = Mat<T, w, h>;	\
using Mat##w##x##h##ub = Mat##w##x##h##<uint8_t>;		\
using Mat##w##x##h##us = Mat##w##x##h##<uint16_t>;		\
using Mat##w##x##h##ui = Mat##w##x##h##<uint32_t>;		\
using Mat##w##x##h##ul = Mat##w##x##h##<uint64_t>;		\
using Mat##w##x##h##b = Mat##w##x##h##<int8_t>;			\
using Mat##w##x##h##s = Mat##w##x##h##<int16_t>;		\
using Mat##w##x##h##i = Mat##w##x##h##<int32_t>;		\
using Mat##w##x##h##l = Mat##w##x##h##<int64_t>;		\
using Mat##w##x##h##f = Mat##w##x##h##<float_t>;		\
using Mat##w##x##h##d = Mat##w##x##h##<double_t>

#define PIRKK_MAT_USING_ALL_TYPES_EVEN(len)				\
template<typename T> using Mat##len = Mat<T, len, len>;	\
using Mat##len##ub = Mat##len##<uint8_t>;				\
using Mat##len##us = Mat##len##<uint16_t>;				\
using Mat##len##ui = Mat##len##<uint32_t>;				\
using Mat##len##ul = Mat##len##<uint64_t>;				\
using Mat##len##b = Mat##len##<int8_t>;					\
using Mat##len##s = Mat##len##<int16_t>;				\
using Mat##len##i = Mat##len##<int32_t>;				\
using Mat##len##l = Mat##len##<int64_t>;				\
using Mat##len##f = Mat##len##<float_t>;				\
using Mat##len##d = Mat##len##<double_t>

		PIRKK_MAT_USING_ALL_TYPES_EVEN(2);
		PIRKK_MAT_USING_ALL_TYPES(2, 2);
		PIRKK_MAT_USING_ALL_TYPES(2, 3);
		PIRKK_MAT_USING_ALL_TYPES(2, 4);
		PIRKK_MAT_USING_ALL_TYPES(3, 2);
		PIRKK_MAT_USING_ALL_TYPES_EVEN(3);
		PIRKK_MAT_USING_ALL_TYPES(3, 3);
		PIRKK_MAT_USING_ALL_TYPES(3, 4);
		PIRKK_MAT_USING_ALL_TYPES(4, 2);
		PIRKK_MAT_USING_ALL_TYPES(4, 3);
		PIRKK_MAT_USING_ALL_TYPES_EVEN(4);
		PIRKK_MAT_USING_ALL_TYPES(4, 4);
	}
}
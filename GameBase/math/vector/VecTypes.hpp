#pragma once

#include "Vec.hpp"

namespace pirkk::math {
	// Define length- and type-specific vectors
#define PIRKK_VEC_USING_ALL_TYPES(len)				\
template<typename T> using Vec##len = Vec<T, len>;	\
using Vec##len##ub = Vec##len##<uint8_t>;			\
using Vec##len##us = Vec##len##<uint16_t>;			\
using Vec##len##ui = Vec##len##<uint32_t>;			\
using Vec##len##ul = Vec##len##<uint64_t>;			\
using Vec##len##b = Vec##len##<int8_t>;				\
using Vec##len##s = Vec##len##<int16_t>;			\
using Vec##len##i = Vec##len##<int32_t>;			\
using Vec##len##l = Vec##len##<int64_t>;			\
using Vec##len##f = Vec##len##<float>;				\
using Vec##len##d = Vec##len##<double>

	PIRKK_VEC_USING_ALL_TYPES(2);
	PIRKK_VEC_USING_ALL_TYPES(3);
	PIRKK_VEC_USING_ALL_TYPES(4);
}
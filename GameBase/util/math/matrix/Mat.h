#pragma once

#include "..\vector\Vec.h"
#include <iostream>
#include <type_traits>

namespace PirkkBase {
	namespace Math {
		template<typename T, size_t W, size_t H>
		struct Mat {
			Vec<T, H> data[W]; // Columns

			Mat(T _data[W * H]) { std::copy(&_data[0], &_data[0] + W * H, &data[0].data[0]); }
			Mat(T _data[W][H]) { std::copy(&_data[0], &_data[0] + W * H, data[0].data[0]); }
			Mat(Vec<T, H> *_data) { std::copy(&_data[0], &_data[0] + W * H, &data[0]); }

			Mat(T _v) { for (size_t x = 0; x < W; x++) for (size_t y = 0; y < H; y++) data[x][y] = (x == y) ? _v : 0; }
			Mat() : Mat(1) {}
			Vec<T, H> &operator[](size_t i) { return data[i]; }
			Vec<T, H> operator[](size_t i) const { return data[i]; }

			void print() const {
				for (size_t i = 0; i < W; i++) {
					std::cout << data[i] << "\n";
				}
			}

			Vec<T, H> getColumn(size_t x) {
				return data[x];
			}

			Vec<T, W> getRow(size_t y) {
				Vec<T, W> out;
				for (size_t i = 0; i < W; i++) out[i] = data[i][y];
				return out;
			}

			static Mat zero() {
				Mat out;
				for (size_t x = 0; x < W; x++) for (size_t y = 0; y < H; y++) out.data[x] = Vec<T, H>();
				return out;
			}
		};

		// Enable printing with std::cout
		template<typename T, size_t W, size_t H>
		std::ostream &operator<<(std::ostream &out, const Mat<T, W, H> &mat) {
			out << "[";
			for (size_t i = 0; i < W; i++) {
				out << mat[i];
				if (i < W - 1) out << ", ";
			}
			out << "]";
			return out;
		}
	}
}

#include "MatOp.h"
#include "MatTypes.h"
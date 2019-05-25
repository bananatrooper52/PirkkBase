#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "../math/Math.hpp"
#include "TextureFormats.hpp"

namespace pirkk::graphics {
	// type, component count, dimensions
	template<typename T, size_t L, size_t D>
	class Texture {
	private:
		using Pixel = pirkk::math::Vec<T, L>;
		using Index = pirkk::math::Vec<unsigned int, D>;
		Index size;
		size_t getLinearSize() {
			size_t out = 1;
			for (size_t i = 0; i < D; i++) {
				out *= size[i];
			}
			return out;
		}

	public:
		std::vector<Pixel> data;

		Texture() : size(Index()), data(std::vector<Pixel>()) {}
		Texture(Index size) : size(size), data(std::vector<Pixel>(getLinearSize())) {}
		Texture(Index size, std::vector<Pixel> data) : size(size), data(data) {
			int expectedSize = getLinearSize();
			if (expectedSize != data.size())
				throw std::runtime_error((std::stringstream() << "Incorrectly sized texture - expected " << std::to_string(expectedSize) <<
					" bytes, but got " << std::to_string(data.size())).str());
		}

		void setPixel(Index pos, Pixel pixel) {
			data[pirkk::math::linearIndex(pos, size)] = pixel;
		}

		const Pixel getPixel(Index pos) {
			return data[pirkk::math::linearIndex(pos, size)];
		}

		const pirkk::math::Vec<unsigned int, D> getSize() const { return size; }
	};
	template<typename T, size_t L> using Texture1D = Texture<T, L, 1>;
	template<typename T, size_t L> using Texture2D = Texture<T, L, 2>;
	template<typename T, size_t L> using Texture3D = Texture<T, L, 3>;
}
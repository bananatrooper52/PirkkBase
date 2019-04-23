#pragma once

#include <string>
#include <vector>

#include "../math/Math.hpp"

namespace pirkk::graphics {
	class Image {
	private:
		pirkk::math::Vec2ui size;

	public:
		std::vector<float> data;

		Image() : size(pirkk::math::Vec2ui(0, 0)), data(std::vector<float>()) {}
		Image(pirkk::math::Vec2ui size) : size(size), data(std::vector<float>((size_t)size.x * (size_t)size.y * 4)) {}
		Image(pirkk::math::Vec2ui size, std::vector<float> data) : size(size), data(data) {
			int expectedSize = size.x * size.y * 4;
			if (expectedSize != data.size())
				throw std::runtime_error(
					"Incorrectly sized texture - expected " +
					std::to_string(expectedSize) +
					" bytes, but got " +
					std::to_string(data.size())
				);
		}

		const pirkk::math::Vec2ui getSize() const { return size; }
		const std::vector<float> getData() const { return data; }
	};
}
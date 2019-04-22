#pragma once

#include <string>
#include <vector>

#include "../math/Math.hpp"

namespace pirkk::graphics {
	class Image {
	private:
		const pirkk::math::Vec2ui size;
		std::vector<unsigned char> data;

	public:
		Image(pirkk::math::Vec2ui size) : size(size), data(std::vector<unsigned char>(size.x* size.y * 4)) {}
		Image(pirkk::math::Vec2ui size, std::vector<unsigned char> data) : size(size), data(data) {
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
		const std::vector<unsigned char> getData() const { return data; }
	};
}
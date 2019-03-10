#include <iostream>

#include "tick/TickManager.h"
#include "util/math/Math.h"

using namespace PirkkBase;

int main() {
	
	Math::Mat4f mat = Math::translate(Math::Mat4f(), Math::Vec3f(10, 0, 0));
	Math::Mat4f mat2 = Math::translate(Math::Mat4f(), Math::Vec3f(0, 0, 10));
	Math::Vec4f test = mat * mat2 * Math::Vec4f(10, 10, 10, 1);

	std::cout << test;

	while (true);
}
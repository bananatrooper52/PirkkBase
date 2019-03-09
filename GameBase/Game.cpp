#include <iostream>

#include "tick/TickManager.h"
#include "util/math/Math.h"

using namespace PirkkBase;

int main() {
	Math::Vec2f vec(1, 2);
	
	Math::Vec2f a[3] = {
		Math::Vec2f(-1, 2),
		Math::Vec2f(0, 0),
		Math::Vec2f(4, 0)
	};

	Math::Vec3f b[2] = {
		Math::Vec3f(-1, -1, 2),
		Math::Vec3f(1, 3, 4)
	};

	Math::Mat3x2f mat(a);
	Math::Mat2x3f bat(b);

	Math::Mat2f out = mat * bat;

	out.print();

	while (true);
}
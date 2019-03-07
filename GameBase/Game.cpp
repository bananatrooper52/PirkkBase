#include <iostream>

#include "tick/TickManager.h"
#include "util/math/vector/VecMath.h"

using namespace PirkkBase;

int main() {
	Vec3f veca(2, 3, 4);
	Vec3f vecb(5, 6, 7);

	std::cout << veca + vecb << std::endl;

	while (true);
}
#include <iostream>

#include "tick/TickManager.h"
#include "util/math/Math.h"

using namespace PirkkBase;

int main() {
	float init[] = {
		1, 4, 7, 10,
		2, 5, 8, 11,
		3, 6, 9, 12
	};

	float meme[] = {
		1, 2, 3, 4,
		4, 5, 6, 5,
		7, 8, 9, 6
	};

	Math::Mat3x4f mat(init);
	Math::Mat3x4f sec(meme);

	std::cout << sec.getRow(0) << std::endl;

	while (true);
}
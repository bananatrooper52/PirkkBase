#pragma once

#include "graphics/Window.hpp"
#include "ticking/TickManager.hpp"

using namespace Pirkk::Math;
using namespace Pirkk::Ticking;
using namespace Pirkk::Graphics;

class Game {
private:
	TickManager tickManager;
	Window window;

public:
	Game();
	void tick(float delta);
	void render();
};
#pragma once

#include "graphics/Window.h"
#include "tick/TickManager.h"

using namespace PirkkBase::Graphics;
using namespace PirkkBase::Math;
using namespace PirkkBase::Ticking;

class Game {
private:
	TickManager tickManager;
	Window window;

public:
	Game();
	void tick(float delta);
	void render();
};
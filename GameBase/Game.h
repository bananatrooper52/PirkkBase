#pragma once

#include "graphics/Window.h"
#include "tick/TickManager.h"

using namespace PirkkBase;

class Game {
private:
	TickManager tickManager;
	Window window;

public:
	Game();
	void tick(float delta);
	void render();
};
#pragma once

#include <memory>

#include "graphics/Window.hpp"
#include "ticking/TickManager.hpp"

class Game {
private:
	pirkk::ticking::TickManager tickManager;
	std::shared_ptr<pirkk::graphics::Window> window;

	void addRegistries();

public:
	Game();
	void tick(float delta);
	void render();
};
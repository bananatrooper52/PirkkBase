#include <iostream>

#include "Game.h"
#include "tick/TickManager.h"
#include "math/Math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Game::Game() : window(Math::Vec2i(1366, 768), "Game") {
	window.makeContextCurrent();

	tickManager.registerCallback("tick", new TickCallback([=](float delta) { tick(delta); }, 1.f / 60.f));
	tickManager.registerCallback("render", new TickCallback([=](float delta) { render(); }, 1.f / 60.f));
	tickManager.start();

}

void Game::tick(float delta) {

	if (window.shouldClose()) tickManager.stop();

	window.swapBuffers();
	glfwPollEvents();
}

void Game::render() {

}

int main() {

	glewInit();
	glfwInit();

	Game game;
}
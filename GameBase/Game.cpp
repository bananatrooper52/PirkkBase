#include <iostream>

#include "Game.h"
#include "tick/TickManager.h"
#include "math/Math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"

GLfloat data[] = {
	-1, -1, 0,
	1, -1, 0,
	0, 1, 0
};

GLushort indices[] = {
	0, 1, 2
};

GLuint vao;
GLuint vbo;
GLuint elem;

Shader *shader;

Game::Game() : window(Vec2i(1366, 768), "Game") {

	window.makeContextCurrent();

	if (glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize GLEW");

	shader = new Shader("default");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	shader->bind();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &elem);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	tickManager.registerCallback("tick", new TickCallback([=](float delta) { tick(delta); }, 1.f / 60.f));
	tickManager.registerCallback("render", new TickCallback([=](float delta) { render(); }, 1.f / 60.f));
	tickManager.start();

	glfwTerminate();
}

void Game::tick(float delta) {
	if (window.shouldClose()) tickManager.stop();
}

void Game::render() {
	shader->bind();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

	window.swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
#include <iostream>

#include "Game.h"
#include "tick/TickManager.h"
#include "math/Math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"
#include "graphics/Mesh.h"

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
Mesh *mesh;

Game::Game() : window(Vec2i(1366, 768), "Game") {

	window.makeContextCurrent();

	if (glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize GLEW");

	shader = new Shader("default");

	mesh = new Mesh(shader);
	mesh->genElementBuffer(GL_STATIC_DRAW, GL_UNSIGNED_SHORT);
	mesh->elementBufferData(indices, sizeof(indices), 3);
	mesh->genBuffer("vertex", GL_STATIC_DRAW, 3, GL_FLOAT, GL_FALSE, 0);
	mesh->bufferData("vertex", data, sizeof(data));

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
	
	mesh->render();

	GLenum glerr = glGetError();
	if (glerr) std::cout << "OpenGL Error " << glerr << ": " << gluErrorString(glerr) << std::endl;

	window.swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
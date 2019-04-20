#include <iostream>

#include "Game.hpp"
#include "ticking/TickManager.hpp"
#include "math/Math.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.hpp"
#include "graphics/Mesh.hpp"

GLfloat data[] = {
	-1, -1, 0,
	1, -1, 0,
	-1, 1, 0,
	1, 1, 0
};

GLushort indices[] = {
	0, 1, 2, 1, 3, 2
};

GLuint vao;
GLuint vbo;
GLuint elem;

Shader *shader;
Mesh *mesh;

Vec3f cameraPos(0);
Mat4f cameraRot(1);

float t;

Vec3f position;

Game::Game() : window(Vec2i(1366, 768), "Game") {

	window.makeContextCurrent();

	if (glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize GLEW");

	shader = new Shader("default");

	mesh = new Mesh(shader);
	mesh->genElementBuffer(GL_STATIC_DRAW, GL_UNSIGNED_SHORT);
	mesh->elementBufferData(indices, sizeof(indices), 6);
	mesh->genBuffer("vertex", GL_STATIC_DRAW, 3, GL_FLOAT, GL_FALSE, 0);
	mesh->bufferData("vertex", data, sizeof(data));
	mesh->getShader()->uniform1f("aspect", window.aspectRatio());

	tickManager.registerCallback("tick", new TickCallback([&](float delta) { tick(delta); }, 1.f / 60.f));
	tickManager.registerCallback("render", new TickCallback([&](float delta) { render(); }, 1.f / 60.f));
	tickManager.start();

	delete shader;
	delete mesh;

	glfwTerminate();
}

void Game::tick(float delta) {
	if (window.shouldClose()) tickManager.stop();

	if (window.getKey(GLFW_KEY_W)) cameraPos.z -= delta;
	if (window.getKey(GLFW_KEY_S)) cameraPos.z += delta;
	if (window.getKey(GLFW_KEY_A)) cameraPos.x -= delta;
	if (window.getKey(GLFW_KEY_D)) cameraPos.x += delta;
	if (window.getKey(GLFW_KEY_LEFT_SHIFT)) cameraPos.y -= delta;
	if (window.getKey(GLFW_KEY_SPACE)) cameraPos.y += delta;

	if (window.getKey(GLFW_KEY_R)) {
		shader->reload();
		mesh->getShader()->uniform1f("aspect", window.aspectRatio());
	}

	t += delta;
	//cameraPos.x = sin(t);

	// TODO: y seems to affect z
	//cameraPos.y = cos(t);
}

void Game::render() {
	shader->uniform3f("cameraPos", cameraPos);
	shader->uniform4x4f("cameraRot", cameraRot);

	mesh->render();

	// GLenum glerr = glGetError();
	// if (glerr) std::cout << "OpenGL Error " << glerr << ": " << gluErrorString(glerr) << std::endl;

	window.swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
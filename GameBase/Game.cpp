#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <numeric>

#include "Game.hpp"
#include "ticking/TickManager.hpp"
#include "math/Math.hpp"
#include "graphics/Shader.hpp"
#include "graphics/mesh/Mesh.hpp"
#include "util/registry/Registry.hpp"
#include "util/registry/RegistryHandler.hpp"
#include "graphics/mesh/ScreenCoverMesh.hpp"
#include "util/FileLoader.hpp"
#include "graphics/raytracing/RaytraceShader.hpp"
#include "graphics/Texture.hpp"

using namespace pirkk::util::registry;
using namespace pirkk::math;
using namespace pirkk::ticking;
using namespace pirkk::graphics;
using namespace pirkk::graphics::mesh;

std::shared_ptr<Mesh> screenMesh;
std::shared_ptr<RaytraceShader> shader;

Vec3f cameraPos(0);
Mat4f cameraRot;
Vec2ui winSize(1024, 768);
unsigned int pixScale = 1;

float t;

float*** terrain;

Vec3f position;

Game::Game() {

	addRegistries();

	Texture3D<float, 3> tex(Vec3ui(32, 32, 1));

	tex.data[0] = Vec3f(1, 0, 1);

	shader->setTexture("tex", tex);

	tickManager.registerCallback("tick", tickCallback = new TickCallback([&](float delta) { tick(delta); }, 1.f / 60.f));
	tickManager.registerCallback("render", renderCallback = new TickCallback([&](float delta) { render(); }, 1.f / 60.f));
	tickManager.start();

	glfwTerminate();
}

void Game::addRegistries() {
	std::shared_ptr<Registry<Window>> windowRegistry = RegistryHandler::addRegistry<Window>();
	window = std::shared_ptr<Window>((new Window(Vec2i(winSize), "Game"))->makeContextCurrent());
	windowRegistry->registerEntry("main", window);
	if (glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize GLEW"); // Initialize GLEW after window context is ready

	std::shared_ptr<Registry<Shader>> shaderRegistry = RegistryHandler::addRegistry<Shader>();
	shader = std::static_pointer_cast<RaytraceShader>(Shader::loadShader("screenCover"));
	shaderRegistry->registerEntry("screenCover", shader);

	std::shared_ptr<Registry<Mesh>> meshRegistry = RegistryHandler::addRegistry<Mesh>();
	screenMesh = std::shared_ptr<Mesh>(new ScreenCoverMesh());
	meshRegistry->registerEntry("raytraceScreen", screenMesh);
}

void Game::tick(float delta) {
	if (window->shouldClose()) tickManager.stop();

	if (window->getKey(GLFW_KEY_R)) {
		shader->reload();
	}

	float mouseSpeed = 0.003f;
	Vec2f mouseMove = window->getMousePos() - Vec2f(winSize) / 2.f;
	float roll = 0;
	if (window->getKey(GLFW_KEY_Q)) roll += delta;
	if (window->getKey(GLFW_KEY_E)) roll -= delta;
	cameraRot = rotate(Vec3f(cameraRot * Vec4f(0, 1, 0, 0)), -mouseMove.x * mouseSpeed) * cameraRot;
	cameraRot = rotate(Vec3f(cameraRot * Vec4f(1, 0, 0, 0)), -mouseMove.y * mouseSpeed) * cameraRot;
	cameraRot = rotate(Vec3f(cameraRot * Vec4f(0, 0, 1, 0)), roll) * cameraRot;

	window->setMousePos(Vec2f(winSize) / 2.f);

	Vec3f moveZ = Vec3f(cameraRot * Vec4f(0, 0, 1, 0)) * delta;
	Vec3f moveX = Vec3f(cameraRot * Vec4f(1, 0, 0, 0)) * delta;
	Vec3f moveY = Vec3f(cameraRot * Vec4f(0, 1, 0, 0)) * delta;

	if (window->getKey(GLFW_KEY_W)) cameraPos -= moveZ;
	if (window->getKey(GLFW_KEY_S)) cameraPos += moveZ;
	if (window->getKey(GLFW_KEY_A)) cameraPos -= moveX;
	if (window->getKey(GLFW_KEY_D)) cameraPos += moveX;
	if (window->getKey(GLFW_KEY_LEFT_SHIFT)) cameraPos -= moveY;
	if (window->getKey(GLFW_KEY_SPACE)) cameraPos += moveY;

	if (window->getKey(GLFW_KEY_ESCAPE)) window->setShouldClose(true);

	t += delta;
}

void Game::render() {
	window->setTitle(std::to_string(renderCallback->getTps()));

	shader->uniform1f("t", sin(t) * 10.f);
	shader->uniform2i("winSize", Vec2i(winSize));
	shader->uniform3f("cameraPos", cameraPos);
	shader->uniform4x4f("cameraRot", cameraRot);

	screenMesh->render();

	window->swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
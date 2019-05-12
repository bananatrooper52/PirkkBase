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

Image img;

Game::Game() {

	size_t TERRAIN_SIZE = 32;

	for (size_t x = 0; x < TERRAIN_SIZE; x++) {
		for (size_t z = 0; z < TERRAIN_SIZE; z++) {
			float height = rand() % 16;
			for (size_t y = 0; y < TERRAIN_SIZE; y++) {
				if (y < height) y = 1;
			}
		}
	}

	addRegistries();

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
	cameraRot = rotate(Vec3f(0, 1, 0), mouseMove.x * mouseSpeed) * cameraRot;

	window->setMousePos(Vec2f(winSize) / 2.f);

	Vec3f moveZ = Vec3f(cameraRot * Vec4f(0, 0, 1, 0) * delta) * Vec3f(-1, 1, 1);
	Vec3f moveX = Vec3f(cameraRot * Vec4f(1, 0, 0, 0) * delta) * Vec3f(1, 1, -1);
	Vec3f moveY = Vec3f(cameraRot * Vec4f(0, 1, 0, 0) * delta);

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

	shader->uniformSphere(Shader::arrName("spheres", 0), { Vec3f(-2, sin(t), -4), 0.6f, Vec3f(1, 0, 1), 0 });
	shader->uniformSphere(Shader::arrName("spheres", 1), { Vec3f(-1, sin(t + 0.2 * pi<float>() * 2), -4), 0.6f, Vec3f(0.5, 0.5, 0.5), 0 });
	shader->uniformSphere(Shader::arrName("spheres", 2), { Vec3f(0, sin(t + 0.4 * pi<float>() * 2), -4), 0.6f, Vec3f(1, 0.5, 0.2), 1 });
	shader->uniformSphere(Shader::arrName("spheres", 3), { Vec3f(1, sin(t + 0.6 * pi<float>() * 2), -4), 0.6f, Vec3f(0.5, 1, 0.6), 0 });
	shader->uniformSphere(Shader::arrName("spheres", 4), { Vec3f(2, sin(t + 0.8 * pi<float>() * 2), -4), 0.6f, Vec3f(0.4, 0.1, 1), 0 });
	shader->uniform1i("sphereCount", 5);

	screenMesh->render();

	window->swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
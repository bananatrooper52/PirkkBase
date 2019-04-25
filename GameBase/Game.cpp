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
Mat4f cameraRot(1);
Vec2ui winSize(1024, 768);
unsigned int pixScale = 1;

float t;

Vec3f position;

Image img;

Game::Game() {
	addRegistries();

	shader->uniformSphere(Shader::arrName("spheres", 0), { Vec3f(-2, 0, -4), 0.45f });
	shader->uniformSphere(Shader::arrName("spheres", 1), { Vec3f(-1, 0, -4), 0.45f });
	shader->uniformSphere(Shader::arrName("spheres", 2), { Vec3f(0, 0, -4), 0.45f });
	shader->uniformSphere(Shader::arrName("spheres", 3), { Vec3f(1, 0, -4), 0.45f });
	shader->uniformSphere(Shader::arrName("spheres", 4), { Vec3f(2, 0, -4), 0.45f });

	shader->uniform1i("sphereCount", 5);

	tickManager.registerCallback("tick", tickCallback = new TickCallback([&](float delta) { tick(delta); }, 1.f / 20.f));
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

	if (window->getKey(GLFW_KEY_W)) cameraPos.z -= delta;
	if (window->getKey(GLFW_KEY_S)) cameraPos.z += delta;
	if (window->getKey(GLFW_KEY_A)) cameraPos.x -= delta;
	if (window->getKey(GLFW_KEY_D)) cameraPos.x += delta;
	if (window->getKey(GLFW_KEY_LEFT_SHIFT)) cameraPos.y -= delta;
	if (window->getKey(GLFW_KEY_SPACE)) cameraPos.y += delta;

	if (window->getKey(GLFW_KEY_R)) {
		shader->reload();
	}

	t += delta;
}

void Game::render() {
	window->setTitle(std::to_string(renderCallback->getTps()));

	shader->uniform1f("t", sin(t) * 10.f);
	shader->uniform2i("winSize", Vec2i(winSize));

	screenMesh->render();

	window->swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
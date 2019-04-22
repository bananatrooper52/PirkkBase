#include <iostream>

#include "Game.hpp"
#include "ticking/TickManager.hpp"
#include "math/Math.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.hpp"
#include "graphics/mesh/Mesh.hpp"
#include "util/registry/Registry.hpp"
#include "util/registry/RegistryHandler.hpp"
#include "graphics/mesh/ScreenCoverMesh.hpp"

using namespace pirkk::util::registry;
using namespace pirkk::math;
using namespace pirkk::ticking;
using namespace pirkk::graphics;
using namespace pirkk::graphics::mesh;

std::shared_ptr<Mesh> screenMesh;
std::shared_ptr<Shader> shader;

Vec3f cameraPos(0);
Mat4f cameraRot(1);

float t;

Vec3f position;

Game::Game() {

	addRegistries();

	tickManager.registerCallback("tick", new TickCallback([&](float delta) { tick(delta); }, 1.f / 60.f));
	tickManager.registerCallback("render", new TickCallback([&](float delta) { render(); }, 1.f / 60.f));
	tickManager.start();

	glfwTerminate();
}

void Game::addRegistries() {
	std::shared_ptr<Registry<Window>> windowRegistry = RegistryHandler::addRegistry<Window>();
	window = std::shared_ptr<Window>((new Window(Vec2i(1366, 768), "Game"))->makeContextCurrent());
	windowRegistry->registerEntry("main", window);
	if (glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize GLEW"); // Initialize GLEW after window context is ready

	std::shared_ptr<Registry<Shader>> shaderRegistry = RegistryHandler::addRegistry<Shader>();
	shader = Shader::loadShader("default");
	shaderRegistry->registerEntry("default", shader);

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
		screenMesh->getShader()->uniform1f("aspect", window->aspectRatio());
	}

	t += delta;
}

void Game::render() {
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
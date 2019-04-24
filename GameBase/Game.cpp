#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.hpp>
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

Image img;

void openCLTest() {

	// Select platform
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	std::cout << "Enter desired platform:\n";
	for (size_t i = 0; i < platforms.size(); i++) {
		std::cout << "  " << i << ": " << platforms[i].getInfo<CL_PLATFORM_NAME>() << "\n";
	}
	std::cout << std::endl;
	size_t platformSelect = 0;
	std::cin >> platformSelect;
	cl::Platform platform = platforms[platformSelect];

	// Select device
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
	std::cout << "Enter desired device:\n";
	for (size_t i = 0; i < devices.size(); i++) {
		std::cout << "  " << i << ": " << devices[i].getInfo<CL_DEVICE_NAME>() << "\n";
	}
	std::cout << std::endl;
	size_t deviceSelect = 0;
	std::cin >> deviceSelect;
	cl::Device device = devices[deviceSelect];
	std::cout << "Selected device: " << device.getInfo<CL_DEVICE_NAME>() << "\n";

	// Create context
	cl::Context context(device);

	// Load kernel source
	std::string src = pirkk::util::loadFile("resources/kernels/default.cl");

	cl::Program program(context, src);

	cl_int err = program.build({ device }, "");
	if (err) std::cerr << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);

	cl::Kernel kernel(program, "renderRaytrace");

	img = Image(Vec2ui(1366, 768));

	cl::Buffer buffOut(context, CL_MEM_WRITE_ONLY, img.data.size() * sizeof(cl_int), NULL);

	kernel.setArg(0, buffOut);
	kernel.setArg(1, (int)img.getSize().x);
	kernel.setArg(2, (int)img.getSize().y);

	cl::CommandQueue queue(context, device);

	size_t localWorkSize = 512;
	size_t globalWorkSize = img.data.size() / 4 / localWorkSize * localWorkSize;

	queue.enqueueNDRangeKernel(kernel, NULL, globalWorkSize, localWorkSize);
	queue.enqueueReadBuffer(buffOut, CL_TRUE, 0, globalWorkSize * sizeof(cl_float) * 4, &img.data[0]);

}

Game::Game() {

	openCLTest();

	addRegistries();

	shader->setTexture2D("tex", img);

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
	shader = Shader::loadShader("screenCover");
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
	screenMesh->render();

	window->swapBuffers();
	glfwPollEvents();
}

int main() {
	if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
	Game game;
}
#include "Window.hpp"

using namespace pirkk::graphics;
using namespace pirkk::math;

Window::Window(Vec2i size, std::string title) {
	window = glfwCreateWindow(size.x, size.y, title.c_str(), 0, 0);
	if (window == NULL) throw std::runtime_error("Failed to open window");
}

Window::~Window() {
	glfwDestroyWindow(window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

Window *Window::makeContextCurrent() {
	glfwMakeContextCurrent(window);
	return this;
}

Vec2i Window::getSize() {
	Vec2i size;
	glfwGetWindowSize(window, &size.x, &size.y);
	return size;
}

void Window::setSize(Vec2i size) {
	glfwSetWindowSize(window, size.x, size.y);
}

float Window::aspectRatio() {
	Vec2f size = Vec2f(getSize());
	return size.x / size.y;
}

void Window::setTitle(std::string title) {
	glfwSetWindowTitle(window, title.c_str());
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool shouldClose) {
	glfwSetWindowShouldClose(window, shouldClose);
}

bool Window::getKey(int key) {
	return glfwGetKey(window, key);
}

Vec2f Window::getMousePos() {
	math::Vec2d pos;
	glfwGetCursorPos(window, &pos.x, &pos.y);
	return Vec2f(pos);
}

void Window::setMousePos(Vec2f pos) {
	glfwSetCursorPos(window, pos.x, pos.y);
}
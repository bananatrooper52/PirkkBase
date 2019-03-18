#include "Window.h"

using namespace PirkkBase::Graphics;
using namespace PirkkBase::Math;

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

void Window::makeContextCurrent() {
	glfwMakeContextCurrent(window);
}

Vec2i Window::getSize() {
	Vec2i size;
	glfwGetWindowSize(window, &size.x, &size.y);
	return size;
}

void Window::setSize(Vec2i size) {
	glfwSetWindowSize(window, size.x, size.y);
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
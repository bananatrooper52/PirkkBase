#include "Window.h"

namespace PirkkBase {
	Window::Window(Math::Vec2i size, std::string title) {
		window = glfwCreateWindow(size.x, size.y, title.c_str(), 0, 0);
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

	Math::Vec2i Window::getSize() {
		Math::Vec2i size;
		glfwGetWindowSize(window, &size.x, &size.y);
		return size;
	}

	void Window::setSize(Math::Vec2i size) {
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
}
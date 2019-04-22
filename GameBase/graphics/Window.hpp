#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../math/Math.hpp"

namespace pirkk::graphics {
	class Window {
	private:
		// Internal GLFW window object
		GLFWwindow* window;

	public:
		Window(math::Vec2i size, std::string title);
		~Window();

		// Swap buffers
		void swapBuffers();

		// Set window as current OpenGL rendering context
		Window *makeContextCurrent();

		// Size getter and setter
		math::Vec2i getSize();
		void setSize(math::Vec2i size);

		float aspectRatio();

		// Title setter
		void setTitle(std::string title);

		// Should close getter and setter
		bool shouldClose();
		void setShouldClose(bool shouldClose);

		// Get whether a key is being pressed
		bool getKey(int key);

		// Get and set mouse position in window
		math::Vec2f getMousePos();
		void setMousePos(math::Vec2f pos);
	};
}
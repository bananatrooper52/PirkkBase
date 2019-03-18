#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../math/Math.h"

namespace PirkkBase {
	namespace Graphics {
		class Window {
		private:
			// Internal GLFW window object
			GLFWwindow *window;

		public:
			Window(Math::Vec2i size, std::string title);
			~Window();

			// Swap buffers
			void swapBuffers();

			// Set window as current OpenGL rendering context
			void makeContextCurrent();

			// Size getter and setter
			Math::Vec2i getSize();
			void setSize(Math::Vec2i size);

			// Title setter
			void setTitle(std::string title);

			// Should close getter and setter
			bool shouldClose();
			void setShouldClose(bool shouldClose);
		};
	}
}
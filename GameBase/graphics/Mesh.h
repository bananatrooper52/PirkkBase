#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "VertexBuffer.h"

namespace PirkkBase {
	namespace Graphics {
		class Mesh {
		private:
			GLuint vao;
			std::map<const char *, VertexBuffer> buffers;

		public:
			void init();
			void genBuffer(const char *name, GLenum target, GLenum usage, GLenum type, GLsizei elemSize, GLsizei dataSize, void *data);
			void render();
			void bindVao();
		};
	}
}
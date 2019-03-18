#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "VertexBuffer.h"
#include "Shader.h"

namespace PirkkBase {
	namespace Graphics {
		class Mesh {
		private:
			GLuint vao;
			VertexBuffer elementBuffer;
			std::map<const char *, VertexBuffer> buffers;
			Shader *shader;
			GLsizei elementCount;

		public:
			Mesh(Shader *shader);
			void genBuffer(const char *name, GLenum usage, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride);
			void bufferData(const char *name, const void *data, GLsizeiptr size);
			void genElementBuffer(GLenum usage, GLenum type);
			void elementBufferData(const void *data, GLsizeiptr size, GLsizei elementCount);
			void render();
			void bindVao();
		};
	}
}
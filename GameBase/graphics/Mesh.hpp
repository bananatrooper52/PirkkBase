#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "VertexBuffer.hpp"
#include "Shader.hpp"

namespace Pirkk::Graphics {
	class Mesh {
	protected:
		GLuint vao;
		VertexBuffer elementBuffer;
		GLsizei elementCount;
		std::map<const char *, VertexBuffer> buffers;
		Shader *shader;

	public:
		Mesh(Shader *shader);
		void genBuffer(const char *name, GLenum usage, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride);
		void bufferData(const char *name, const void *data, GLsizeiptr size);
		void genElementBuffer(GLenum usage, GLenum type);
		void elementBufferData(const void *data, GLsizeiptr size, GLsizei elementCount);
		void drawElements(GLenum mode, GLenum type, const void *indices = NULL);
		virtual void render();
		void bindVao();
		Shader *getShader();
	};
}
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace PirkkBase {
	namespace Graphics {
		class VertexBuffer {
		private:
			// The id of the buffer object
			GLuint id;

			// Render mode (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc)
			GLenum usage;

			// Render target (GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER)
			GLenum target;

			// The name of the "in" variable in shader
			const char *name;

		public:
			VertexBuffer(const char *name, GLenum usage, GLenum target);
			VertexBuffer(GLenum usage, GLenum target);
			VertexBuffer();
			VertexBuffer(const VertexBuffer &other);

			// Bind this buffer object
			void bind() const;

			// Upload data to the buffer object
			void setData(const void *data, GLsizeiptr length) const;

			void setUsage(GLenum usage);

			bool valid() const;
		};
	}
}
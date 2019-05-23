#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <typeinfo>

namespace pirkk::graphics {
	class GLTypes {
	public:
		// Get an OpenGL enum value for a data type (e.g. GLfloat type to GL_FLOAT enum value)
		template<typename T> constexpr static GLenum getGLTypeEnum(T val = 0) { throw std::exception("Invalid type"); }

#define PIRKK_GL_TYPE(type, typeEnum) template<> static GLenum getGLTypeEnum<type>(type val) { return typeEnum; }

		PIRKK_GL_TYPE(GLubyte, GL_UNSIGNED_BYTE);
		PIRKK_GL_TYPE(GLbyte, GL_BYTE);
		PIRKK_GL_TYPE(GLushort, GL_UNSIGNED_SHORT);
		PIRKK_GL_TYPE(GLshort, GL_SHORT);
		PIRKK_GL_TYPE(GLuint, GL_UNSIGNED_INT);
		PIRKK_GL_TYPE(GLint, GL_INT);
		PIRKK_GL_TYPE(GLfloat, GL_FLOAT);
		PIRKK_GL_TYPE(GLdouble, GL_DOUBLE);
	};
}
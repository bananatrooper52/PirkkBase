#pragma once

#include "../math/Math.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string>

using namespace PirkkBase::Math;

namespace PirkkBase {
	namespace Graphics {
		class Shader {
		private:
			std::string name;
			GLuint id;
			std::map<const char *, GLint> uniformLocations;
			std::map<const char *, GLint> attributeLocations;

			// Load vertex or fragment source string
			GLuint loadShaderSource(std::string src, GLenum type);
			
			// Check for errors in compiled program
			void verifyProgram();

			void compileProgram();

		public:
			Shader(std::string name);

			void bind();
			GLint getUniformLocation(const char *name);
			GLint getAttributeLocation(const char *name);
			std::string getName();

			void uniform1f(const char *name, float v);
			void uniform2f(const char *name, Vec2f v);
			void uniform3f(const char *name, Vec3f v);
			void uniform4f(const char *name, Vec4f v);
			void uniform1i(const char *name, int v);
			void uniform2i(const char *name, Vec2i v);
			void uniform3i(const char *name, Vec3i v);
			void uniform4i(const char *name, Vec4i v);
			void uniform3x3f(const char *name, Mat3f v, bool transpose = false);
			void uniform4x4f(const char *name, Mat4f v, bool transpose = false);
		};
	}
}
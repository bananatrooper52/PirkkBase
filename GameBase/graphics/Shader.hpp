#pragma once

#include "../math/Math.hpp"
#include "Image.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <vector>

namespace pirkk::graphics {
	class Shader {
	private:
		std::string name;
		GLuint id;
		std::map<const char*, GLint> uniformLocations;
		std::map<const char*, GLint> attributeLocations;
		std::map<const char*, GLuint> textureIds;

		// Load vertex or fragment source string
		GLuint loadShaderSource(std::string src, GLenum type);

		// Check for errors in compiled program
		void verifyProgram();

		void compileProgram();

	public:
		static std::shared_ptr<Shader> loadShader(std::string name);

		Shader(std::string name);

		void bind();
		GLint getUniformLocation(const char* name);
		GLint getAttributeLocation(const char* name);
		GLuint getTextureId(const char* name);
		std::string getName();

		// Reload the source for the shader
		void reload();

		void uniform1f(const char* name, float v);
		void uniform2f(const char* name, pirkk::math::Vec2f v);
		void uniform3f(const char* name, pirkk::math::Vec3f v);
		void uniform4f(const char* name, pirkk::math::Vec4f v);
		void uniform1i(const char* name, int v);
		void uniform2i(const char* name, pirkk::math::Vec2i v);
		void uniform3i(const char* name, pirkk::math::Vec3i v);
		void uniform4i(const char* name, pirkk::math::Vec4i v);
		void uniform3x3f(const char* name, pirkk::math::Mat3f v, bool transpose = false);
		void uniform4x4f(const char* name, pirkk::math::Mat4f v, bool transpose = false);

		void setTexture2D(const char* name, const Image &data);
	};
}
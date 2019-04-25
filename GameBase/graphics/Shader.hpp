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
		std::map<std::string, GLint> uniformLocations;
		std::map<std::string, GLint> attributeLocations;
		std::map<std::string, GLuint> textureIds;

		// Load vertex or fragment source string
		GLuint loadShaderSource(std::string src, GLenum type);

		// Check for errors in compiled program
		void verifyProgram();

		void compileProgram();

	public:
		static std::shared_ptr<Shader> loadShader(std::string name);

		Shader(std::string name);

		void bind();
		GLint getUniformLocation(std::string name);
		GLint getAttributeLocation(std::string name);
		GLuint getTextureId(std::string name);
		std::string getName();

		// Reload the source for the shader
		void reload();

		void uniform1f(std::string name, float v);
		void uniform2f(std::string name, pirkk::math::Vec2f v);
		void uniform3f(std::string name, pirkk::math::Vec3f v);
		void uniform4f(std::string name, pirkk::math::Vec4f v);
		void uniform1fv(std::string name, std::vector<float> v);
		void uniform2fv(std::string name, std::vector<pirkk::math::Vec2f> v);
		void uniform3fv(std::string name, std::vector<pirkk::math::Vec3f> v);
		void uniform4fv(std::string name, std::vector<pirkk::math::Vec4f> v);
		void uniform1i(std::string name, int v);
		void uniform2i(std::string name, pirkk::math::Vec2i v);
		void uniform3i(std::string name, pirkk::math::Vec3i v);
		void uniform4i(std::string name, pirkk::math::Vec4i v);
		void uniform1iv(std::string name, std::vector<int> v);
		void uniform2iv(std::string name, std::vector<pirkk::math::Vec2i> v);
		void uniform3iv(std::string name, std::vector<pirkk::math::Vec3i> v);
		void uniform4iv(std::string name, std::vector<pirkk::math::Vec4i> v);
		void uniform3x3f(std::string name, pirkk::math::Mat3f v, bool transpose = false);
		void uniform4x4f(std::string name, pirkk::math::Mat4f v, bool transpose = false);

		void setTexture2D(std::string name, const Image &data);

		// arrName("a", 0) -> "a[0]"
		static std::string arrName(std::string name, size_t index);

		// memberName("a", "b") -> "a.b"
		static std::string memberName(std::string name, std::string memberName);
	};
}
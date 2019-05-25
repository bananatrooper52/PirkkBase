#pragma once

#include "../math/Math.hpp"
#include "Texture.hpp"
#include "GLTypes.hpp"

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

		// Reload the source for the shader from file
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

		template<typename T, size_t L, size_t D>
		void setTexture(std::string name, Texture<T, L, D>& tex) {

			constexpr GLenum format = TextureFormats::getGLFormatEnum(L);
			GLenum type = GLTypes::getGLTypeEnum<T>();
			pirkk::math::Vec<unsigned int, D> size = tex.getSize();
			void* data = &tex.data[0][0];
			GLenum target;

			switch (D) {
			case 1: target = GL_TEXTURE_1D; break;
			case 2: target = GL_TEXTURE_2D; break;
			case 3: target = GL_TEXTURE_3D; break;
			default: throw std::exception("Invalid texture size");
			}


			switch (D) {
			case 1: glTexImage1D(target, 0, format, size.x, 0, format, type, data); break;
			case 2: glTexImage2D(target, 0, format, size.x, size.y, 0, format, type, data); break;
			case 3: glTexImage3D(target, 0, format, size.x, size.y, size.z, 0, format, type, data); break;
			}
			
			glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
			glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		// arrName("a", 0) -> "a[0]"
		static std::string arrName(std::string name, size_t index);

		// memberName("a", "b") -> "a.b"
		static std::string memberName(std::string name, std::string memberName);
	};
}
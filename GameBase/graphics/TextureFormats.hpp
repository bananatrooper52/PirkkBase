#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pirkk::graphics {
	class TextureFormats {
	public:
		enum Format {
			R,
			RG,
			RGB,
			BGR,
			RGBA,
			BGRA,
			D,
			DS
		};

		// Get the OpenGL format enum
		constexpr static GLenum getGLFormatEnum(Format format) {
			switch (format) {
			case R: return GL_R;
			case RG: return GL_RG;
			case RGB: return GL_RGB;
			case BGR: return GL_BGR;
			case RGBA: return GL_RGBA;
			case BGRA: return GL_BGRA;
			case D: return GL_DEPTH_BUFFER;
			case DS: return GL_DEPTH_STENCIL;
			}
		}

		constexpr static GLenum getGLFormatEnum(size_t components) {
			switch (components) {
			case 1: return GL_RED;
			case 2: return GL_RG;
			case 3: return GL_RGB;
			case 4: return GL_RGBA;
			}
		}
	};
}
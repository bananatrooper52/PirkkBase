#pragma once

#include "Mesh.hpp"
#include "../../util/registry/RegistryHandler.hpp"
#include "../Window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pirkk::graphics::mesh {
	class ScreenCoverMesh : public Mesh {
	private:

	public:
		ScreenCoverMesh() : Mesh(pirkk::util::registry::RegistryHandler::getRegistry<Shader>()->getEntryValue("default")) {
			GLfloat data[] = {
				-1, -1, 0,
				1, -1, 0,
				-1, 1, 0,
				1, 1, 0
			};

			GLushort indices[] = {
				0, 1, 2, 1, 3, 2
			};

			genElementBuffer(GL_STATIC_DRAW, GL_UNSIGNED_SHORT);
			elementBufferData(indices, sizeof(indices), 6);
			genBuffer("vertex", GL_STATIC_DRAW, 3, GL_FLOAT, GL_FALSE, 0);
			bufferData("vertex", data, sizeof(data));
			getShader()->uniform1f("aspect", pirkk::util::registry::RegistryHandler::getRegistry<Window>()->getEntryValue("main")->aspectRatio());
		}
	};
}
#pragma once

#include "../Shader.hpp"
#include "../../math/Math.hpp"

class RaytraceShader : public pirkk::graphics::Shader {
public:
	struct Sphere {
		pirkk::math::Vec3f c;
		float r;
		pirkk::math::Vec3f color;
		float emission;
	};

	void uniformSphere(std::string name, Sphere sphere);
};
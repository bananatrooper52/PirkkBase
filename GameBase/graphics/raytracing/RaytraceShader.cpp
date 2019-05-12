#include "RaytraceShader.hpp"

void RaytraceShader::uniformSphere(std::string name, Sphere sphere) {
	uniform3f(Shader::memberName(name, "c"), sphere.c);
	uniform1f(Shader::memberName(name, "r"), sphere.r);
	uniform3f(Shader::memberName(name, "color"), sphere.color);
	uniform1f(Shader::memberName(name, "emission"), sphere.emission);
}
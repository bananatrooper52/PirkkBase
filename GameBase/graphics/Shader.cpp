#include "Shader.hpp"
#include "../util/FileLoader.hpp"

using namespace pirkk::graphics;
using namespace pirkk::math;

std::shared_ptr<Shader> Shader::loadShader(std::string name) {
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(name);
	shader->compileProgram();
	return shader;
}

Shader::Shader(std::string name) : name(name), id(0) {}

GLuint Shader::loadShaderSource(std::string src, GLenum type) {
	GLuint shaderId = glCreateShader(type);

	const GLchar* srcCstr = src.c_str();

	glShaderSource(shaderId, 1, &srcCstr, 0);
	glCompileShader(shaderId);

	return shaderId;
}

void Shader::verifyProgram() {
	GLint logLen;
	GLint result = 0;

	glGetProgramiv(id, GL_LINK_STATUS, &result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);

	if (logLen > 0) {
		GLchar* msg = new GLchar[logLen];
		glGetProgramInfoLog(id, logLen, 0, msg);
		std::cout << msg << std::endl;
		delete[] msg;
	}
}

void Shader::compileProgram() {
	std::string vertSrc = util::loadFile("resources/shaders/" + name + "/vert.glsl");
	std::string fragSrc = util::loadFile("resources/shaders/" + name + "/frag.glsl");

	const GLchar * vertSrcPtr = vertSrc.c_str();
	const GLchar * fragSrcPtr = fragSrc.c_str();

	GLuint vertId = loadShaderSource(vertSrcPtr, GL_VERTEX_SHADER);
	GLuint fragId = loadShaderSource(fragSrcPtr, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertId);
	glAttachShader(id, fragId);
	glLinkProgram(id);

	verifyProgram();

	glDetachShader(id, vertId);
	glDeleteShader(vertId);

	glDetachShader(id, fragId);
	glDeleteShader(fragId);
}

void Shader::bind() {
	glUseProgram(id);
}

GLint Shader::getUniformLocation(const char* name) {
	std::map<const char*, GLint>::iterator it = uniformLocations.find(name);
	if (it == uniformLocations.end()) {
		GLint location = glGetUniformLocation(id, name);
		return uniformLocations[name] = location;
	}
	return uniformLocations[name];
}

GLint Shader::getAttributeLocation(const char* name) {
	std::map<const char*, GLint>::iterator it = attributeLocations.find(name);
	if (it == attributeLocations.end()) {
		GLint location = glGetAttribLocation(id, name);
		attributeLocations[name] = location;
		return location;
	}
	return it->second;
}

GLuint Shader::getTextureId(const char* name) {
	std::map<const char*, GLuint>::iterator it = textureIds.find(name);
	if (it == textureIds.end()) {
		GLuint tex = 0;
		glGenTextures(1, &tex);
		textureIds[name] = tex;
		return tex;
	}
	return it->second;
}

std::string Shader::getName() {
	return name;
}

void Shader::reload() {
	compileProgram();
}

void Shader::uniform1f(const char* name, float v) { bind(); glUniform1f(getUniformLocation(name), v); }
void Shader::uniform2f(const char* name, Vec2f v) { bind(); glUniform2f(getUniformLocation(name), v.x, v.y); }
void Shader::uniform3f(const char* name, Vec3f v) { bind(); glUniform3f(getUniformLocation(name), v.x, v.y, v.z); }
void Shader::uniform4f(const char* name, Vec4f v) { bind(); glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w); }
void Shader::uniform1i(const char* name, int v) { bind(); glUniform1i(getUniformLocation(name), v); }
void Shader::uniform2i(const char* name, Vec2i v) { bind(); glUniform2i(getUniformLocation(name), v.x, v.y); }
void Shader::uniform3i(const char* name, Vec3i v) { bind(); glUniform3i(getUniformLocation(name), v.x, v.y, v.z); }
void Shader::uniform4i(const char* name, Vec4i v) { bind(); glUniform4i(getUniformLocation(name), v.x, v.y, v.z, v.w); }
void Shader::uniform3x3f(const char* name, Mat3f v, bool transpose) { glUniformMatrix3fv(getUniformLocation(name), 1, transpose, &v[0][0]); }
void Shader::uniform4x4f(const char* name, Mat4f v, bool transpose) { glUniformMatrix4fv(getUniformLocation(name), 1, transpose, &v[0][0]); }

void Shader::setTexture2D(const char* name, const Image &image) {
	glBindTexture(GL_TEXTURE_2D, getTextureId(name));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.getData()[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
#include "Mesh.hpp"

using namespace pirkk::graphics;
using namespace pirkk::graphics::mesh;

Mesh::Mesh(std::shared_ptr<Shader> shader) : shader(shader), elementCount(0) {
	glGenVertexArrays(1, &vao);
}

void Mesh::genBuffer(const char *name, GLenum usage, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride) {
	bindVao();

	VertexBuffer buff(name, usage, GL_ARRAY_BUFFER);
	buff.bind();

	buffers[name] = buff;

	// Find attribute location in shader
	GLint attr = shader->getAttributeLocation(name);

	// Warn if the attribute doesn't exist
	if (attr == -1) {
		std::cout << "Couldn't find attribute '" << name << "' [" << shader->getName() << "]" << std::endl;
		return;
	}

	// Enable vertex attrib array
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, size, type, normalized, stride, (void *)0);
}

void Mesh::bufferData(const char *name, const void *data, GLsizeiptr size) {
	bindVao();
	buffers[name].setData(data, size);
}

void Mesh::genElementBuffer(GLenum usage, GLenum type) {
	bindVao();
	VertexBuffer buff(usage, GL_ELEMENT_ARRAY_BUFFER);
	elementBuffer = buff;
}

void Mesh::elementBufferData(const void *data, GLsizeiptr size, GLsizei elementCount) {
	bindVao();
	elementBuffer.setData(data, size);
	this->elementCount = elementCount;
}

void Mesh::drawElements(GLenum mode, GLenum type, const void* indices) {
	bindVao();
	shader->bind();
	elementBuffer.bind();
	glDrawElements(mode, elementCount, type, indices);
}

void Mesh::render() {
	drawElements(GL_TRIANGLES, GL_UNSIGNED_SHORT);
}

void Mesh::bindVao() {
	glBindVertexArray(vao);
}

std::shared_ptr<Shader> Mesh::getShader() {
	return shader;
}
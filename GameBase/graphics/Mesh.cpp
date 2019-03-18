#include "Mesh.h"

using namespace PirkkBase::Graphics;

void Mesh::init() {
	glGenVertexArrays(1, &vao);
}

void Mesh::genBuffer(const char *name, GLenum target, GLenum usage, GLenum type, GLsizei elemSize, GLsizei dataSize, void *data) {
	bindVao();
	GLuint buff = 0;
	glGenBuffers(1, &buff);
	glBufferData(target, dataSize, data, usage);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, elemSize, type, GL_FALSE, 0, NULL);
}

void Mesh::render() {
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
}

void Mesh::bindVao() {
	glBindVertexArray(vao);
}
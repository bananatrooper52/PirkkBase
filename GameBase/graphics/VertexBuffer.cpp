#include "VertexBuffer.h"
#include <iostream>

using namespace PirkkBase::Graphics;

VertexBuffer::VertexBuffer(const char *name, GLenum usage, GLenum target) :
	name(name),
	usage(usage),
	target(target)
{
	glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer(GLenum usage, GLenum target) :
	name(nullptr),
	usage(usage),
	target(target)
{
	glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer() :
	name(nullptr),
	usage(NULL),
	target(NULL)
{}

VertexBuffer::VertexBuffer(const VertexBuffer &other) :
	id(id),
	name(other.name),
	usage(other.usage),
	target(other.target)
{}

void VertexBuffer::bind() const {
	glBindBuffer(target, id);
}

void VertexBuffer::setData(const void *data, GLsizeiptr length) const {
	bind();
	glBufferData(target, length, data, usage);
}

void VertexBuffer::setUsage(GLenum usage) {
	this->usage = usage;
}

bool VertexBuffer::valid() const {
	return id != 0 && usage != 0 && target != NULL;
}
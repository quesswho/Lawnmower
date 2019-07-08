#include "Buffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
{
	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VertexBufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/////////////

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
	: m_Count(count)
{
	glGenBuffers(1, &m_IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_IndexBufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//////////////////////

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

void VertexArray::AddVertexBuffer(const VertexBuffer &vertexBuffer)
{
	unsigned int index = 0;
	glBindVertexArray(m_VertexArrayID);
	vertexBuffer.Bind();

	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
}

void VertexArray::AddIndexBuffer(const IndexBuffer &indexBuffer)
{
	glBindVertexArray(m_VertexArrayID);
	m_IndexBuffer = &indexBuffer;
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
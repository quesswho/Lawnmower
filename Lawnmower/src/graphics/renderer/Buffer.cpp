#include "Buffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const float* vertices, unsigned int size)
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

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
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

void VertexArray::AddTextureBuffer(const std::shared_ptr<VertexBuffer> &TextureCoords, unsigned int index)
{
	glBindVertexArray(m_VertexArrayID);
	TextureCoords->Bind();
	glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(index);
	m_VertexBuffers.push_back(TextureCoords);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, unsigned int index)
{
	glBindVertexArray(m_VertexArrayID);
	vertexBuffer->Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(index);
	m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
	glBindVertexArray(m_VertexArrayID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
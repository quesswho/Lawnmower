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

//vec2
void VertexArray::AddTextureBuffer(const std::shared_ptr<VertexBuffer>& textureCoords, unsigned int stride, unsigned int offset, unsigned int index)
{
	glBindVertexArray(m_VertexArrayID);
	textureCoords->Bind();
	glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(index);
	m_VertexBuffers.push_back(textureCoords);
}

//vec3
void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, unsigned int stride, unsigned int offset, unsigned int index)
{
	glBindVertexArray(m_VertexArrayID);
	vertexBuffer->Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
	glEnableVertexAttribArray(index);
	m_VertexBuffers.push_back(vertexBuffer);
}

//vec4
void VertexArray::AddColorBuffer(const std::shared_ptr<VertexBuffer>& colorBuffer, unsigned int stride, unsigned int offset, unsigned int index)
{
	glBindVertexArray(m_VertexArrayID);
	colorBuffer->Bind();
	glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
	glEnableVertexAttribArray(index);
	m_VertexBuffers.push_back(colorBuffer);
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
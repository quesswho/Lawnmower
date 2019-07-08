#pragma once
#include <vector>
#include <memory>

class VertexBuffer {
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_VertexBufferID;
};

class IndexBuffer {
private:
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int getCount() const { return m_Count; }
private:
	unsigned int m_IndexBufferID;
};

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const VertexBuffer &vertexBuffer);
	void AddIndexBuffer(const IndexBuffer &indexBuffer);

	const std::vector<VertexBuffer*> getVertexBuffers() const { return m_VertexBuffers; }
	const IndexBuffer* getIndexBuffer() const { return m_IndexBuffer; }
private:
	unsigned int m_VertexArrayID;
	std::vector<VertexBuffer*> m_VertexBuffers;
	const IndexBuffer* m_IndexBuffer;
};
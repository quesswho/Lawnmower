#pragma once
#include <vector>
#include <memory>

class VertexBuffer {
public:
	VertexBuffer(const float* vertices, unsigned int size);
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
	IndexBuffer(const unsigned int* indices, unsigned int count);
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

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer, unsigned int index);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer);

	const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers() const { return m_VertexBuffers; }
	const std::shared_ptr<IndexBuffer> &getIndexBuffer() const { return m_IndexBuffer; }
private:
	unsigned int m_VertexArrayID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};
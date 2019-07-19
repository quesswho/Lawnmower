#pragma once
#include <vector>
#include <memory>

class VertexBuffer {
public:
	VertexBuffer(const float* vertices, const unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_VertexBufferID;
};

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* indices, const unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }
private:
	const unsigned int m_Count;
	unsigned int m_IndexBufferID;
};

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer, unsigned int stride, unsigned int offset, unsigned int index);
	void AddColorBuffer(const std::shared_ptr<VertexBuffer>& colorBuffer, unsigned int stride, unsigned int offset, unsigned int index);
	void AddTextureBuffer(const std::shared_ptr<VertexBuffer> &TextureCoords, unsigned int stride, unsigned int offset, unsigned int index);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer);

	inline const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers() const { return m_VertexBuffers; }
	inline const std::shared_ptr<IndexBuffer> &getIndexBuffer() const { return m_IndexBuffer; }
private:
	unsigned int m_VertexArrayID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};
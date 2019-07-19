#include "Renderer.h"
#include <GL/glew.h>

#define RENDERER_MAX_SPRITES	2530

Renderer::Renderer(unsigned int bufferSize)
{
	m_Buffer.reset(new VertexArray());
	m_Buffer->Bind();
	m_VertexBuffer.reset(new VertexBuffer(NULL, sizeof(PointData) * 4 * bufferSize)); //data is set in Submit(*), pre allocate memory
	m_Buffer->AddVertexBuffer(m_VertexBuffer, sizeof(PointData), 0, 0);
	m_Buffer->AddVertexBuffer(m_VertexBuffer, sizeof(PointData), 3 * sizeof(GLfloat), 1);

	GLuint* indices = new GLuint[bufferSize * 4 * 6];

	int offset = 0;
	for (int i = 0; i < bufferSize * 4 * 6; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 3;

		indices[i + 3] = offset + 1;
		indices[i + 4] = offset + 2;
		indices[i + 5] = offset + 3;

		offset += 4; // 4 points after applying indices to cuboid/rectangle
	}

	m_IndexBuffer = new IndexBuffer(indices, bufferSize * 4 * 6);

	m_Buffer->Unbind();
	
	
}

Renderer::~Renderer()
{
	delete m_IndexBuffer;
	m_VertexBuffer->~VertexBuffer();
}

void Renderer::Clear(const float x, const float y, const float z)
{
	glClearColor(x, y, z, 1.0);
}

void Renderer::Begin()
{
	
	m_VertexBuffer->Bind();
	m_Points = (PointData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); //opengl should read m_Batch
}

void Renderer::End()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	m_VertexBuffer->Unbind();
}

void Renderer::Submit(const Sprite* sprite)
{
	const glm::vec3& position = sprite->getPosition();
	const glm::vec2& size = sprite->getSize();
	const glm::vec4& color = sprite->getColor();

	m_Points->vertex = position;
	m_Points->color = color;
	m_Points++;

	m_Points->vertex = glm::vec3(position.x, position.y + size.y, position.z);
	m_Points->color = color;
	m_Points++;

	m_Points->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
	m_Points->color = color;
	m_Points++;

	m_Points->vertex = glm::vec3(position.x + size.x, position.y, position.z);
	m_Points->color = color;
	m_Points++;

	m_IndexCount += 6;


}

void Renderer::Submit(const TexturedSprite texsprite)
{
	m_TexSprites.push_back(texsprite);
}

void Renderer::Draw()
{
	//Render simple sprites without texture
	m_Buffer->Bind();
	m_IndexBuffer->Bind();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	m_IndexBuffer->Unbind();
	m_Buffer->Unbind();

	m_IndexCount = 0;

	//Render sprite with Texture and different shader
	while (!m_TexSprites.empty())
	{
		TexturedSprite sprite = m_TexSprites.back();
		sprite.Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Enable transparency for the texture
		glDrawElements(GL_TRIANGLES, sprite.getIndexCount(), GL_UNSIGNED_INT, 0);
		glDisable(GL_BLEND);
		m_TexSprites.pop_back();
	}
}
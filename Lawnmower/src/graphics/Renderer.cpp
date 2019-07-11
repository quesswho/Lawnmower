#include "Renderer.h"
#include <GL/glew.h>
Renderer::Renderer()
{
	//setup camera
}

void Renderer::Begin() 
{

}

void Renderer::End()
{

}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
	m_Sprites.push_back(vertexArray);
}

void Renderer::Draw()
{
	std::shared_ptr<VertexArray> temp = nullptr;
	for (std::vector<std::shared_ptr<VertexArray>>::iterator iteration = m_Sprites.begin(); iteration != m_Sprites.end(); iteration++)
	{
		temp = *iteration;
		temp->Bind();
		glDrawElements(GL_TRIANGLES, temp->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}
}
#include "Window.h"
#include <iostream>

Window::Window(unsigned int width, unsigned int height, const char* title)
	: m_width(width), m_height(height), m_title(title)
{
	if (!init())
	{
		//Failed to create window
		Window::~Window();
	}
	std::cout << "Successfully created window!\n";
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";
		return false;
	}
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!m_window)
	{
		std::cout << "Failed to create Window!\n";
		return false;
	}
	glfwMakeContextCurrent(m_window);

	if (!glewInit() == GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!\n";
		return false;
	}
	return true;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

bool Window::Running()
{
	return !glfwWindowShouldClose(m_window);
}
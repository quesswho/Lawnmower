#include "Window.h"
#include <Windows.h>
#include <iostream>

void window_resize(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods);

Window::Window(unsigned int width, unsigned int height, const char* title)
	: m_width(width), m_height(height), m_title(title)
{
	if (!init())
	{ Window::~Window(); }
	memset(m_keys, 0, sizeof(m_keys));
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
	glfwSetWindowUserPointer(m_window, this);
	glfwSetWindowSizeCallback(m_window, window_resize);
	glfwSetKeyCallback(m_window, key_callback);

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

void window_resize(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height); //Update opengl viewport to stretch frames to new window size properties
}

void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	Window* winptr = (Window*)glfwGetWindowUserPointer(window);
	winptr->m_keys[keycode] = Action(action);
}
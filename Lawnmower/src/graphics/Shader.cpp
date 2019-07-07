#include "Shader.h"
#include "util/ReadFile.h"
#include <GL/glew.h>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	if (!init(vertexPath, fragmentPath))
	{
	}
}

Shader::~Shader()
{}

bool Shader::init(const char* vertexPath, const char* fragmentPath)
{
	const char* vertexCode = readFile(vertexPath);
	const char* fragmentCode = readFile(fragmentPath);

	unsigned int vertexID, fragmentID;
	char infoLog[512];
	int status;

	//////////////////////////////////////////////
	//////////VERTEX SHADER///////////////////////
	//////////////////////////////////////////////

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexCode, NULL);
	glCompileShader(vertexID);
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader " << infoLog << "\n";
		return false;
	}

	//////////////////////////////////////////////
	//////////FRAGMENT SHADER/////////////////////
	//////////////////////////////////////////////

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentCode, NULL);
	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		std::cout << "Error compiling fragment shader " << infoLog << "\n";
		return false;
	}

	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vertexID);
	glAttachShader(m_ShaderID, fragmentID);
	glLinkProgram(m_ShaderID);

	glGetShaderiv(m_ShaderID, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(m_ShaderID, 512, NULL, infoLog);
		std::cout << "Error linking shader " << infoLog << "\n";
		return false;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	return true;
}

void Shader::Bind()
{
	glUseProgram(m_ShaderID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::getLocation(const char* name)
{ 
	return glGetUniformLocation(m_ShaderID, name);
}
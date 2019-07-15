#pragma once
#include <glm/mat4x4.hpp>

class Shader {
private:
	unsigned int m_ShaderID;
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform1i(const char* uniform, int value);
	void setUniformMat4x4(const char* uniform, glm::mat4x4 value);
private:
	unsigned int getLocation(const char* name);
	bool init(const char* vertexPath, const char* fragmentPath);
};
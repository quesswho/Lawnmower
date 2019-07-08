#pragma once

class Shader {
private:
	unsigned int m_ShaderID;
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int getLocation(const char* name);
	bool init(const char* vertexPath, const char* fragmentPath);
};
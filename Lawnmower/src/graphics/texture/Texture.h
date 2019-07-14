#pragma once

class Texture {
private:
	int m_Width, m_Height, m_Channel;
public:
	Texture(const char* texturePath);
	~Texture();

	void Bind() const;
	void Unbind() const;

	void BindtoValue(unsigned int value);

private:
	unsigned int m_TextureID;
};
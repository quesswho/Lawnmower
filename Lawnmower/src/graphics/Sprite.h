#pragma once
#include <glm/vec2.hpp>


class Sprite {
public:
	Sprite(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color)
		: m_Position(position), m_Size(size), m_Color(color) {}
	Sprite(const glm::vec2 position, const glm::vec2 size, const glm::vec3 f_colors) //lazy constructor
		: Sprite(glm::vec3(position, 0.0), size, glm::vec4(f_colors, 0.0)) {}
	~Sprite() {}

	inline const glm::vec3& getPosition() const { return m_Position; }
	inline const glm::vec2& getSize() const { return m_Size; }
	inline const glm::vec4& getColor() const { return m_Color; }
protected:
	const glm::vec3 m_Position;
	const glm::vec2 m_Size;
	const glm::vec4 m_Color;
};
#version 330 core
layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec4 l_color;

out vec4 v_color;

void main()
{
    gl_Position = vec4(l_pos, 1.0);
	v_color = l_color;
}
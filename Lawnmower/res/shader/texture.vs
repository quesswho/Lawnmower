#version 330 core
layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec4 l_color;
layout (location = 2) in vec2 l_texcoords;

out vec4 v_color;
out vec2 v_texcoords;

uniform mat4 model_matrix = mat4(1.0);

void main()
{
    gl_Position = model_matrix * vec4(l_pos, 1.0);
	v_color = l_color;
	v_texcoords = vec2(l_texcoords.x, l_texcoords.y);
}
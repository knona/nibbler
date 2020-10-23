#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 inColor;

out vec3 color;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(pos, 0.0, 1.0);
	color = inColor;
}

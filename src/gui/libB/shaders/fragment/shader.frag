#version 330 core
uniform vec3 color;

out vec4 outFrag;

void main()
{
	outFrag = vec4(color, 1.0);
}

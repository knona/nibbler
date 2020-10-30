#version 330 core
in vec2 texCoord;

uniform vec3 color;
uniform sampler2D tex;
uniform bool isColor;

out vec4 outFrag;


void main()
{
	if (isColor)
		outFrag = vec4(color, 1.0);
	else
		outFrag = texture(tex, texCoord);
}

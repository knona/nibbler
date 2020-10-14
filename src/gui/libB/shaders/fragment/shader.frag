#version 330 core
in vec3 color;
in vec2 texCoord;

out vec4 outFrag;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main()
{
    // outFrag = vec4(color, 1.0);
	outFrag = mix(texture(texture1, texCoord), texture(texture2, vec2(texCoord.x, texCoord.y)), mixValue);
}

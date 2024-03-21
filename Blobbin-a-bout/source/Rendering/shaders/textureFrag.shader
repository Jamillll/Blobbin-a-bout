#version 450 core

layout(location = 0) in vec2 textureCoords;

out vec4 fragColour;

uniform sampler2D texture2D;

void main()
{
	fragColour = texture(texture2D, textureCoords);
}
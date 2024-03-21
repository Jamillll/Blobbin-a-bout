#version 450 core

layout(location = 0) in vec4 colour;

layout(location = 0) out vec4 fragColour;

void main()
{
	fragColour = colour;
}
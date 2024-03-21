#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColour;

layout(location = 0) out vec4 colour;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	colour = vertexColour;
}
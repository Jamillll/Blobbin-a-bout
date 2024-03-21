 #version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexTextureCoords;

layout(location = 0) out vec2 textureCoords;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	textureCoords = vec2(vertexTextureCoords.x, vertexTextureCoords.y);
}
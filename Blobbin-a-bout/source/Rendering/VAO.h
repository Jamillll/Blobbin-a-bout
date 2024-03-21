#pragma once
#include <GL/glew.h>
#include <vector>
#include "../Types.h"

class VAO
{
private:
	unsigned int vaoID, vboID, eboID;
	int usage = GL_DYNAMIC_DRAW;
	unsigned int indicesCount;

	unsigned int attributeCount = 0;
	unsigned int stride = 0;

public:

	VAO()
	{
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		glGenBuffers(1, &eboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	}

	void AddVertexAttribute(unsigned int size, int type, unsigned int sizeofType, bool normalised, unsigned int vertexSize)
	{
		BindVAO();
		glVertexAttribPointer(attributeCount, size, type, normalised, vertexSize, (void*)stride);
		glEnableVertexAttribArray(attributeCount);

		stride += (sizeofType * size);
		attributeCount++;
	}

	void WriteToVertexBuffer(void* vertexArray, unsigned int bufferSize)
	{
		BindVAO();
		glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexArray, usage);
	}

	void WriteToIndexBuffer(unsigned int* indexArray, unsigned int indexArrayCount)
	{
		BindVAO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexArrayCount, indexArray, usage);

		indicesCount = indexArrayCount;
	}

	unsigned int GetVaoId()
	{
		return vaoID;
	}

	void BindVAO()
	{
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	}

	void UnbindVAO()
	{
		glBindVertexArray(0);
	}

	void DrawVAO()
	{
		BindVAO();
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	}
};
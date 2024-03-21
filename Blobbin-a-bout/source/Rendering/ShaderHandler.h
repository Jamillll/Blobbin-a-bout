#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderHandler
{
public:
	unsigned int programID = 0;

public:
	ShaderHandler(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		programID = glCreateProgram();

		unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, ParseShader(vertexShaderPath));
		getShaderErrors(vertexShader, GL_COMPILE_STATUS, "Vertex Shader");
		glAttachShader(programID, vertexShader);
		glDeleteShader(vertexShader);

		unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ParseShader(fragmentShaderPath));
		getShaderErrors(fragmentShader, GL_COMPILE_STATUS, "Fragment Shader");
		glAttachShader(programID, fragmentShader);
		glDeleteShader(fragmentShader);

		glLinkProgram(programID);
		glValidateProgram(programID);

		int succeeded;
		glGetProgramiv(programID, GL_VALIDATE_STATUS, &succeeded);

		if (succeeded == false)
		{
			GLsizei length;
			char error[1024];
			glGetProgramInfoLog(programID, 1024, &length, error);

			std::cout << "The Shader program has encountered error " << error << std::endl;
		}

		glUseProgram(programID);
	}

	void setTextureUniform(const char* uniformName, int value)
	{
		glUseProgram(programID);

		int location = glGetUniformLocation(programID, uniformName);
		if (location == -1) std::cout << "ERROR! Uniform not found" << std::endl;
		
		glUniform1i(location, value);
	}

	void setVector4Uniform(const char* uniformName, const float* value)
	{
		glUseProgram(programID);

		int location = glGetUniformLocation(programID, uniformName);
		if (location == -1) std::cout << "ERROR! Uniform not found" << std::endl;

		glUniform4fv(location, 4, value);
	}

	void setUniformMat4f(const char* uniformName, glm::mat4& matrix)
	{
		glUseProgram(programID);

		int location = glGetUniformLocation(programID, uniformName);
		if (location == -1) std::cout << "ERROR! Uniform not found" << std::endl;

		glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
	}

	void setIntUniform(const char* uniformName, int value)
	{
		glUseProgram(programID);

		int location = glGetUniformLocation(programID, uniformName);
		if (location == -1) std::cout << "ERROR! Uniform not found" << std::endl;

		glUniform1i(location, value);
	}

	void setFloatUniform(const char* uniformName, float value)
	{
		glUseProgram(programID);

		int location = glGetUniformLocation(programID, uniformName);
		if (location == -1) std::cout << "ERROR! Uniform not found" << std::endl;

		glUniform1f(location, value);
	}

	void UseShaders()
	{
		glUseProgram(programID);
	}

private:
	std::string ParseShader(std::string shaderPath)
	{
		std::fstream file(shaderPath);
		std::string shader;
		std::string currentLine;

		while (getline(file, currentLine))
		{
			shader += currentLine + "\n";
		}

		//std::cout << shader << std::endl;

		return shader;
	}

	unsigned int CompileShader(unsigned int type, std::string shader)
	{
		unsigned int id = glCreateShader(type);
		const char* source = shader.c_str();
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		return id;
	}

	void getShaderErrors(unsigned int shaderID, unsigned int logQueryEnum, std::string shaderType)
	{
		int succeeded;
		glGetShaderiv(shaderID, logQueryEnum, &succeeded);

		if (succeeded == false)
		{
			GLsizei length;
			char error[1024];
			glGetShaderInfoLog(shaderID, 1024, &length, error);

			std::cout << shaderType << " has encountered error " << error << std::endl;
		}
	}
};
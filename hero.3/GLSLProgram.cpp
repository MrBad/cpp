//
// Created by vio on 8/15/17.
//

#include "GLSLProgram.h"
#include <fstream>
#include <vector>
#include "Error.h"

GLSLProgram::GLSLProgram() :
		programID(0),
		vertexShaderID(0),
		fragmentShaderID(0),
		numAttributes(0)
{

}

GLSLProgram::~GLSLProgram()
{

}



void GLSLProgram::compileShaders(const std::string &shaderFilePath)
{
	programID = glCreateProgram();

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {
		fatalError("Cannot create vertex shader");
	}
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {
		fatalError("Cannot create fragment shader");
	}

	this->compileShader(shaderFilePath + ".vs", vertexShaderID);
	this->compileShader(shaderFilePath + ".fs", fragmentShaderID);

}

void GLSLProgram::linkShaders()
{

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if(isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog((unsigned long)maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(programID);
		//Don't leak shaders either.
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Cannot link shaders!");
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}



void GLSLProgram::compileShader(const std::string &filePath, GLuint &shaderID)
{
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		fatalError("Cannot open " + filePath);
	}
	std::string content = "";
	std::string line;
	while (std::getline(vertexFile, line)) {
		content += line + "\n";
	}
	vertexFile.close();

	const char *contentPtr = content.c_str();
	glShaderSource(shaderID, 1, &contentPtr, nullptr);

	glCompileShader(shaderID);

	// error handling //
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(shaderID);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Cannot create shader: " + filePath);
	}
}

void GLSLProgram::addAttribute(const std::string &attributeName)
{
	glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
}

void GLSLProgram::use()
{
	glUseProgram(programID);
	for(int i = 0; i < numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}

}

void GLSLProgram::unuse(){
	glUseProgram(0);
	for(int i = 0; i < numAttributes; i++) {
		glEnableVertexAttribArray(0);
	}
}

GLuint GLSLProgram::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(programID, uniformName.c_str());
	if(location == GL_INVALID_INDEX) {
		fatalError("Uniform: " + uniformName + " not found in shader");
	}
	return location;
}

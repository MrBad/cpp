//
// Created by vio on 8/15/17.
//

#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>
//#include "Error.h"

class GLSLProgram {

public:
	GLSLProgram();
	virtual ~GLSLProgram();

	void compileShaders(const std::string & shadersPath);
	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);
	void use();
	void unuse();


private:

	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	GLint numAttributes;
	void compileShader(const std::string& shaderFilePath, GLuint& shaderID);
};


#endif //GLSLPROGRAM_H

#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <fstream>
#include <GL/glew.h>
extern bool errorFound;
class Shader
{
	const GLchar *vertexSourceFile;
	const GLchar *fragmentSourceFile;
	GLuint id;
public:
	Shader(const GLchar *vertexSource, const GLchar *fragmentSource);
	void compileCheck(GLuint &shader);
	void linkCheck(GLuint &program);
	GLuint createShaderProgram(const GLchar *vertex, const GLchar *fragment);
	const GLchar* readShaderFile(const char* filePath);
	void useProgram();
	GLint getUniform(const GLchar *uniform);
};
#endif

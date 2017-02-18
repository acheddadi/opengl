#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <GL\glew.h>
#include <SOIL\SOIL.h>
class Texture
{
	GLint width, height;
public:
	GLuint id;
	Texture(const GLchar *filename, GLint width, GLint height, GLboolean mipMap = false);
	void bindTexture();
};
#endif
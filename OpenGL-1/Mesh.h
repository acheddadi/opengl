#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <GL/glew.h>
class Mesh
{
public:
	GLuint VBO, VAO, EBO;
	Mesh(GLfloat *data, GLint size = 9 * sizeof(GL_FLOAT), GLuint *indice = NULL, GLint indiceSize = 6 * sizeof(GL_UNSIGNED_INT));
	~Mesh();
};
#endif


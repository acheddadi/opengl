#include "Mesh.h"
Mesh::Mesh(GLfloat *data, GLint size, GLuint *indice, GLint indiceSize)
{
	GLuint stride;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	if (indice != NULL)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, indice, GL_STATIC_DRAW);
	}
	if (size == 18 * sizeof(GL_FLOAT))
	{
		stride = 6 * sizeof(GL_FLOAT);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
	}
	else if (size == 32 * sizeof(GL_FLOAT))
	{
		stride = 8 * sizeof(GL_FLOAT);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);
	}
	else if (size == 180 * sizeof(GL_FLOAT))
	{
		stride = 5 * sizeof(GL_FLOAT);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);
	}
	else
	{
		stride = 3 * sizeof(GL_FLOAT);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	}
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
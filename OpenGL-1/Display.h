#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Display
{
	GLchar* TITLE;
	GLint WIDTH, HEIGHT;
	GLFWwindow *window;
public:
	GLFWwindow *id;
	Display(GLchar* title, GLint width, GLint height);
	~Display();
};
#endif

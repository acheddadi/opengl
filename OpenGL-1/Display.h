#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Display
{
	GLchar* TITLE;
	GLint WIDTH, HEIGHT;
	GLFWwindow *window;
public:
	GLFWwindow *id;
	Display(GLchar* title, GLint width, GLint height);
	~Display();
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode); //Pointer to window, key pressed, scancode (???), action of key (presse, depressed), bitflag mode (holding shift, ctrl etc.)
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};
#endif

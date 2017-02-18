#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Common.h"

GLfloat mixLevel = 0.2f, opacityLevel = 1.0f;
bool keys[];
bool rotate = false;

class Display
{
	bool firstMouse;
	GLfloat lastX, lastY, pitch, yaw;
	GLchar* TITLE;
	GLint WIDTH, HEIGHT;
	GLFWwindow *window;
	glm::vec3 cameraPos, cameraFront, cameraUp, cameraTarget;
	glm::mat4 camera;
	GLfloat deltaTime;	// Time between current frame and last frame
	GLfloat lastFrame;  	// Time of last frame
public:
	GLfloat *view;
	GLFWwindow *id;
	Display(GLchar* title, GLint width, GLint height);
	~Display();
	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode); //Pointer to window, key pressed, scancode (???), action of key (presse, depressed), bitflag mode (holding shift, ctrl etc.)
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void doMovement();
};
#endif

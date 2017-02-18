#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Common.h"
class Camera
{
	GLboolean firstMouse;
	GLfloat lastX, lastY, pitch, yaw;
	glm::vec3 cameraPos, cameraFront, cameraUp, cameraTarget;
	glm::mat4 camera;
	GLfloat deltaTime;	// Time between current frame and last frame
	GLfloat lastFrame;  	// Time of last frame

public:
	GLfloat *id;
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));
	~Camera();
	void keyMovement();
	void mouseMovement();
};
#endif
#include "Camera.h"
GLfloat lastX, lastY, pitch, yaw;
Camera::Camera(glm::vec3 position)
{
	//Initializing camera pointer
	id = glm::value_ptr(camera);

	//Initializing deltatime for constant movement speed.
	deltaTime = 0.0f;	// Time between current frame and last frame
	lastFrame = 0.0f;  	// Time of last frame

	//Initializing camera matrices.
	cameraPos = position;
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//Initializing mouse variables.
	firstMouse = true;
	lastX = WIDTH / 2.0f; lastY = HEIGHT / 2.0f;
}


Camera::~Camera()
{
}
void Camera::keyMovement()
{
	// Calculate deltatime of current frame
	GLfloat currentFrame = (GLfloat)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void Camera::mouseMovement()
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xoffset = xPos - lastX;
	GLfloat yoffset = lastY - yPos; // Reversed since y-coordinates go from bottom to left
	lastX = xPos;
	lastY = yPos;

	GLfloat sensitivity = 0.05f;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	cameraTarget = cameraPos + cameraFront;
	camera = glm::lookAt(cameraPos, cameraTarget, cameraUp);   //Pos, target pos, up vector.
}
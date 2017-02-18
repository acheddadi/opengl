#include "Display.h"
Display::Display(GLchar* title, GLint width, GLint height)
{
	//Initializing camera pointer
	view = glm::value_ptr(camera);
	//Initializing deltatime for constant movement speed.
	deltaTime = 0.0f;	// Time between current frame and last frame
	lastFrame = 0.0f;  	// Time of last frame
	//Initializing camera matrices.
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//Initializing mouse variables.
	firstMouse = true;
	lastX = WIDTH / 2.0f; lastY = HEIGHT / 2.0f;
	WIDTH = width; HEIGHT = height; TITLE = title;
	//Initializing window
	glfwInit();
	/*We can configure GLFW using glfwWindowHint.
	The first argument tells us what option we'd like to configure.
	All options are prefixed with GLFW_.
	The second argument is and integer that sets the value of our option.
	A list of all the possible options and its corresponding values can be found at GLFW's window handling documentation :
	http://www.glfw.org/docs/latest/window.html#window_hints
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Forces openGL 3.x.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Forces openGL x.3.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Uses OpenGL core profile only.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //Non-resizeable window.

	//Create a pointer to object or GLFWwindow class.
	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr); id = window;
	if (window == nullptr) //glfwCreateWindow returns an object of class GLFWwindow with specified parameters.
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		this->~Display();
	}

	//Make the context of 'window' our main context on the current thread.
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback); //Register the keycallback function.
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE; //Ensures GLEW uses more modern techniques for managing OpenGL functionality.
	if (glewInit() != GLEW_OK) //Test glew initialization.
	{
		std::cout << "Failed to initialize GLEW." << std::endl;
	}

	glViewport(0, 0, WIDTH, HEIGHT); //Tell OpenGL the size of the rendering window and display coordinates.
	//First two parameters are the coordinates of the lower left point in the window, cartsesian plane basically.
	//the last two are the display resolution.
}
Display::~Display()
{
	glfwTerminate();
}
void Display::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		if (mixLevel >= 1.0f) mixLevel = 0.0f;
		else mixLevel += 0.1f;
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		if (mixLevel <= 0.0f) mixLevel = 1.0f;
		else mixLevel -= 0.1f;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		//translation = glm::translate(translation, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		//translation = glm::translate(translation, glm::vec3(-0.1f, 0.0f, 0.0f));
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		//translation = glm::translate(translation, glm::vec3(0.0f, 0.1f, 0.0f));
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		//translation = glm::translate(translation, glm::vec3(0.0f, -0.1f, 0.0f));
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (rotate) rotate = false;
		else rotate = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		if (opacityLevel >= 1.0f) opacityLevel = 0.0f;
		else opacityLevel += 0.1f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		if (opacityLevel <= 0.0f) opacityLevel = 1.0f;
		else opacityLevel -= 0.1f;
	}

	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}
void Display::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}

	GLfloat xoffset = (GLfloat)xpos - lastX;
	GLfloat yoffset = lastY - (GLfloat)ypos; // Reversed since y-coordinates go from bottom to left
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;

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
void Display::doMovement()
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
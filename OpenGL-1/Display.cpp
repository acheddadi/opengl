#include "Display.h"
Display::Display(GLchar* title, GLint width, GLint height)
{
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
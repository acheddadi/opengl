#define GLEW_STATIC
#include <GL/glew.h> //GLEW - OpenGL Extension Wrangler Library : Manages function pointers defined by driver.
#include <GLFW/glfw3.h> //GLFW - OpenGL Frame Work : Manages the window aspect of OpenGL without the headache of Win32 API
#include <iostream>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Common.h"
#include "Shader.h"
#include "Mesh.h"
#include "Display.h"
#include "Texture.h"
#include "Camera.h"
const GLuint WIDTH = 1024, HEIGHT = 768;
GLfloat mixLevel = 0.2f;
GLfloat xPos, yPos;
GLboolean rotate = false, errorFound = false, charlieMode = false;
GLboolean keys[];
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode); //Pointer to window, key pressed, scancode (???), action of key (presse, depressed), bitflag mode (holding shift, ctrl etc.)
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void setCallBack(GLFWwindow *window);
int main()
{
	Display myWindow("Triangle madness 2.0", WIDTH, HEIGHT);
	setCallBack(myWindow.id);

	GLfloat rightVertex[] = {
		0.5f, 0.95f, 0.0f,		//Bottom left corner
		0.9f, 0.95f, 0.0f,		//Bottom right corner
		0.7f, 0.55f, 0.0f		//Top middle corner
	};
	GLfloat leftVertex[] = {
		-0.5f, 0.95f, 0.0f,		//Bottom left corner
		-0.9f, 0.955f, 0.0f,	//Bottom right corner
		-0.7f, 0.55f, 0.0f		//Top middle corner
	};
	GLfloat midVertex[] = {
		-0.2f, -0.95f, 0.0f,	//Bottom left
		0.2f, -0.95f, 0.0f,		// Bottom right
		-0.2f, -0.55f, 0.0f,	//Top left
		0.2f, -0.55f, 0.0f		//Top right
	};
	GLuint midIndices[] = {
		0,1,2,
		2,3,1
	};
	GLfloat btmRightVertex[] = {
		//Points			//Colors
		0.5f, -0.95f, 0.0f,	1.0f, 0.0f, 0.0f,	//Bottom left corner	
		0.9f, -0.95f, 0.0f,	0.0f, 1.0f, 0.0f,	//Bottom right corner
		0.7f, -0.55f, 0.0f,	0.0f, 0.0f, 1.0f	//Top middle corner
	};
	GLfloat btmLeftVertex[] = {
		//Points			
		-0.5f, -0.95f, 0.0f,		//Bottom left corner	
		-0.9f, -0.95f, 0.0f, 		//Bottom right corner
		-0.7f, -0.55f, 0.0f 		//Top middle corner
	};
	GLfloat textureContainer[] = {
		//Points			//Colors			//Texture Coordinates
		-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	1.0f, 0.0f
	};
	GLuint contIndices[] = {
		0, 1, 2,
		2, 3, 1
	};
	GLfloat cube[] = {
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f,

		0.5f, 0.5f, 0.5f,		1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f
	};
	GLfloat skyCrd[] = {
		-0.5f, -0.5f, -0.5f,	0.0f, 0.33f, //Bottom left
		0.5f, -0.5f, -0.5f,		0.25f, 0.33f, //Bottom right
		0.5f, 0.5f, -0.5f,		0.25f, 0.66f, //Top right
		0.5f, 0.5f, -0.5f,		0.25f, 0.66f, //Top right
		-0.5f, 0.5f, -0.5f,		0.0f, 0.66f, //Top left
		-0.5f, -0.5f, -0.5f,	0.0f, 0.33f, //Bottom left

		-0.5f, -0.5f, 0.5f,		0.75f, 0.33f,//Bottom left
		0.5f, -0.5f, 0.5f,		0.5f, 0.33f,//Bottom right
		0.5f, 0.5f, 0.5f,		0.5f, 0.66f,//Top right
		0.5f, 0.5f, 0.5f,		0.5f, 0.66f,//Top right
		-0.5f, 0.5f, 0.5f,		0.75f, 0.66f,//Top left
		-0.5f, -0.5f, 0.5f,		0.75f, 0.33f,//Bottom left

		-0.5f, 0.5f, 0.5f,		0.75f, 0.66f,//Bottom left
		-0.5f, 0.5f, -0.5f,		1.0f, 0.66f,//Bottom right
		-0.5f, -0.5f, -0.5f,	1.0f, 0.33f,//Top right
		-0.5f, -0.5f, -0.5f,	1.0f, 0.33f,//Top right
		-0.5f, -0.5f, 0.5f,		0.75f, 0.33f,//Top left
		-0.5f, 0.5f, 0.5f,		0.75f, 0.66f,//Bottom left

		0.5f, 0.5f, 0.5f,		0.50f, 0.66f,//Bottom left
		0.5f, 0.5f, -0.5f,		0.25f, 0.66f,//Bottom right
		0.5f, -0.5f, -0.5f,		0.25f, 0.33f,//Top right
		0.5f, -0.5f, -0.5f,		0.25f, 0.33f,//Top right
		0.5f, -0.5f, 0.5f,		0.50f, 0.33f,//Top left
		0.5f, 0.5f, 0.5f,		0.50f, 0.66f,//Bottom left

		-0.5f, -0.49f, -0.5f,	0.25f, 0.0f,//Bottom left
		0.5f, -0.49f, -0.5f,	0.25f, 0.33f,//Bottom right
		0.5f, -0.49f, 0.5f,		0.5f, 0.33f,//Top right
		0.5f, -0.49f, 0.5f,		0.5f, 0.33f,//Top right
		-0.5f, -0.49f, 0.5f,	0.5f, 0.0f,//Top left
		-0.5f, -0.49f, -0.5f,	0.25f, 0.0f,//Bottom left

		-0.5f, 0.5f, -0.5f,		0.25f, 1.0f,//Bottom left
		0.5f, 0.5f, -0.5f,		0.25f, 0.66f,//Bottom right
		0.5f, 0.5f, 0.5f,		0.5f, 0.66f,//Top right
		0.5f, 0.5f, 0.5f,		0.5f, 0.66f,//Top right
		-0.5f, 0.5f, 0.5f,		0.5f, 1.0f,//Top left
		-0.5f, 0.5f, -0.5f,		0.25f, 1.0f //Bottom left
	};
	//Cube positions.
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};
	//Create meshes containing vertices.
	Mesh msh_orgTri(leftVertex),
		msh_ylwTri(rightVertex),
		msh_flckrSqr(midVertex, sizeof(midVertex), midIndices),
		msh_flckrTri(btmLeftVertex),
		msh_rnbwTri(btmRightVertex, sizeof(btmRightVertex)),
		msh_container(textureContainer, sizeof(textureContainer), contIndices),
		msh_cube(cube, sizeof(cube)), msh_sky(skyCrd, sizeof(skyCrd));
	//Create shader program that links both shaders.
	Shader prg_orgTri("vDflt.vert", "fOrg.frag"),
		prg_ylwTri("vDflt.vert", "fYlw.frag"),
		prg_flckrSqr("vDflt.vert", "fFlckr.frag"),
		prg_flckrTri("vRnbw.vert", "fFlckr.frag"),
		prg_rnbwTri("vRnbw.vert", "fRnbw.frag"),
		prg_container("vTxtr.vert", "fTxtr.frag"),
		prg_sky("sky.vert", "sky.frag");
	//Load textures.
	Texture txtr_container("img/container.jpg", 512, 512);
	Texture txtr_face("img/awesomeface.png", 512, 512);
	Texture txtr_sky("img/sky.jpg", 4096, 3072);
	Texture txtr_charlie("img/charlie.jpg", 512, 512);
	//Create transformation matrices.
	glm::mat4 model;
	model = glm::scale(model, glm::vec3(100, 100, 100));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 rotation;
	Camera myCamera(glm::vec3 (0.0f, 0.0f, 3.0f));
	while (!glfwWindowShouldClose(myWindow.id)) //While GLFW window was not instructed to close. Simple game loop.
	{
		glfwPollEvents(); //Checks for any events that are triggered (keyboard or mouse inputs.)
		//... Rendering commands here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); /*At the start of each render iteration we always want to clear the screen otherwise we would still see the results from the previous iteration.
		We can clear the screen's color buffer using the glClear function where we pass in buffer bits to specify which buffer we would like to clear.
		The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.
		Note that we also set a color via glClearColor to clear the screen with. Whenever we call glClear and clear the color buffer, the entire color
		buffer will be filled with the color as configured by glClearColor.*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		if (!errorFound)
		{
			GLdouble timeValue = glfwGetTime();
			GLfloat sinTime = (float)(sin(timeValue) / 2) + 0.5f, cosTime = (float)(cos(timeValue * 2) / 2) + 0.5f;
			GLfloat gVal = sinTime, rVal = cosTime, bVal = cosTime;
			GLfloat gVal2 = cosTime, rVal2 = sinTime, bVal2 = sinTime;
			//Camera actions.
			myCamera.keyMovement();
			myCamera.mouseMovement();
			//Rotation loop.
			if (rotate) rotation = glm::rotate(rotation, glm::radians(0.05f), glm::vec3(0.5f, 0.5f, 1.0f));
			//Left Triangle.
			prg_orgTri.useProgram();
			glBindVertexArray(msh_orgTri.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			//Right Triangle.
			prg_ylwTri.useProgram();
			glBindVertexArray(msh_ylwTri.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			//Middle Square.
			prg_flckrSqr.useProgram();
			glUniform4f(prg_flckrSqr.getUniform("myColor"), rVal, gVal, bVal, 1.0f);
			glBindVertexArray(msh_flckrSqr.VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			//Bottom Right Triangle.
			prg_rnbwTri.useProgram();
			glBindVertexArray(msh_rnbwTri.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			//Bottom Left Triangle.
			prg_flckrTri.useProgram();
			glUniform4f(prg_flckrTri.getUniform("myColor"), rVal2, gVal2, bVal2, 1.0f);
			glBindVertexArray(msh_flckrTri.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			//Center texture.
			prg_sky.useProgram();
			glUniformMatrix4fv(prg_sky.getUniform("model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(prg_sky.getUniform("camera"), 1, GL_FALSE, myCamera.id);
			glUniformMatrix4fv(prg_sky.getUniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glActiveTexture(GL_TEXTURE0);
			txtr_sky.bindTexture();
			glUniform1i(prg_sky.getUniform("myTexture1"), 0);
			glBindVertexArray(msh_sky.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			//Center texture.
			prg_container.useProgram();
			glUniformMatrix4fv(prg_container.getUniform("camera"), 1, GL_FALSE, myCamera.id);
			glUniformMatrix4fv(prg_container.getUniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(prg_container.getUniform("rotation"), 1, GL_FALSE, glm::value_ptr(rotation));/*We first query the location of the uniform variable
																						   and then send the matrix data to the shaders via glUniform 
																						   function with Matrix4fv as its postfix. The first argument 
																						   should be familiar by now which is the uniform's location. 
																						   The second argument tells OpenGL how many matrices we'd like 
																						   to send, which is 1. The third argument asks us if we want to 
																						   transpose our matrix, that is to swap the columns and rows. 
																						   OpenGL developers often use an internal matrix layout called 
																						   column-major ordering which is the default matrix layout in GLM 
																						   so there is no need to transpose the matrices; we can keep it 
																						   at GL_FALSE. The last parameter is the actual matrix data, but 
																						   GLM stores their matrices not in the exact way that OpenGL likes 
																						   to receive them so we first transform them with GLM's built-in 
																						   function value_ptr. */																					
			if (!charlieMode) glUniform1f(prg_container.getUniform("mixLevel"), mixLevel);
			else glUniform1f(prg_container.getUniform("mixLevel"), 1.0f);
			glActiveTexture(GL_TEXTURE0);
			txtr_container.bindTexture();
			glUniform1i(prg_container.getUniform("myTexture1"), 0);
			glActiveTexture(GL_TEXTURE1);
			if (!charlieMode) txtr_face.bindTexture();
			else txtr_charlie.bindTexture();
			glUniform1i(prg_container.getUniform("myTexture2"), 1);
			glBindVertexArray(msh_cube.VAO);
			for (int i = 0; i < 10; i++)
			{
				glm::mat4 newModel;
				newModel = glm::translate(newModel, cubePositions[i]);
				GLfloat angle = 20.0f * i;
				newModel = glm::rotate(newModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				glUniformMatrix4fv(prg_container.getUniform("model"), 1, GL_FALSE, glm::value_ptr(newModel));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			glBindVertexArray(0);
		}
		//Swap buffers.
		glfwSwapBuffers(myWindow.id); /*Double buffer : When an application draws in a single buffer the resulting image might display flickering issues. This is because the resulting
						   output image is not drawn in an instant, but drawn pixel by pixel and usually from left to right and top to bottom. Because these images are not displayed at an inst
						   ant to the user, but rather via a step by step generation the result may contain quite a few artifacts. To circumvent these issues, window
						   ing applications apply a double buffer for rendering. The front buffer contains the final output image that is shown at the screen, while
						   all the rendering commands draw to the back buffer. As soon as all the rendering commands are finished we swap the back buffer to the front buffer
						   so the image is instantly display to the user, removing all of the aforementioned artifacts.*/
	}
	return 0;
}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) keys[key] = true;
	if (action == GLFW_RELEASE) keys[key] = false;
	if (keys[GLFW_KEY_ESCAPE]) glfwSetWindowShouldClose(window, GL_TRUE);
	if (keys[GLFW_KEY_X]){ if (mixLevel >= 1.0f) mixLevel = 0.0f; else mixLevel += 0.1f; }
	if (keys[GLFW_KEY_Z]){ if (mixLevel <= 0.0f) mixLevel = 1.0f; else mixLevel -= 0.1f; }
	if (key == GLFW_KEY_C && action == GLFW_PRESS) if (!charlieMode) charlieMode = true; else charlieMode = false;
	if (key == GLFW_KEY_R && action == GLFW_PRESS) if (!rotate) rotate = true; else rotate = false;
}
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	xPos = (GLfloat)xpos;
	yPos = (GLfloat)ypos;
}
void setCallBack(GLFWwindow *window)
{
	glfwSetKeyCallback(window, key_callback); //Register the keycallback function.
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
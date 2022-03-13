//Phillip Lim, Student, Number: 9157 , repo :github.com/phillip8232
#include <iostream>
#include <sstream>

#define GLEW_STATIC

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "ShaderProgram.h"
#include "Texture2D.h"

const char* APP_TITLE = "Advaced Game Engine with Modern OpenGL";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
const std::string texture1Filename = "airplane.png";
const std::string texture2Filename = "crate.jpg";

bool gFullscreen = false;
GLFWwindow* pWindow = NULL;

bool gWireframe = false;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);
bool initOpenGL();

int selectedNum = 1; //Change this value or use keyboard input to change value to see shape change.


int main()
{
	if (!initOpenGL())
	{
		std::cerr << "GLFW initialized fail." << std::endl;
		return (-1);
	}
	

	//------------------------FIRST--------------------------//
	GLfloat vert_pos[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2,  // First Triangle
		0, 2, 3   // Second Triangle
	};

	GLuint vbo;
	GLuint ibo;
	GLuint vao;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//------------------------SECOND--------------------------//
	GLfloat vert_tri_pos[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	GLuint tri_indices[] = {
		0, 1, 2,  // First Triangle
	};

	GLuint vbo2;
	GLuint ibo2;
	GLuint vao2;

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_tri_pos), vert_tri_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_indices), tri_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);


	//------------------------THIRD---------------------------//
	GLfloat vert_poly_pos[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   //0
		0.5f, 0.0f, 0.0f, 0.0f, 0.0f,   //1
		-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  //2
		0.4f, 0.45f, 0.0f, 0.0f, 0.0f,  //3
		-0.4f, 0.45f, 0.0f, 0.0f, 0.0f, //4
		0.0f, 0.7f,   0.0f, 0.0f, 0.0f, //5
	};

	GLuint poly_indices[] = {
		0, 1, 3,
		0, 3, 5,
		0, 4, 5,
		0, 2, 4,
	};

	GLuint vbo3;
	GLuint ibo3;
	GLuint vao3;

	glGenBuffers(1, &vbo3);
	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_poly_pos), vert_poly_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao3);
	glBindVertexArray(vao3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(poly_indices), poly_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	//--------------------------------------------------//
	ShaderProgram shaderProgram;
	shaderProgram.loadShader("basic.vert", "basic.frag");

	Texture2D texture1;
	texture1.loadTexture(texture1Filename, true);

	Texture2D texture2;
	texture2.loadTexture(texture2Filename, true);

	while (!glfwWindowShouldClose(pWindow))
	{
		showFPS(pWindow);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		texture1.bind(0);
		texture2.bind(1);

		//activate a program
		shaderProgram.use();

		glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "myTexture1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "myTexture2"), 1);

		GLfloat time = glfwGetTime();
		glm::vec2 pos;
		pos.x = sin(time) / 2;
		pos.y = cos(time) / 2;

		shaderProgram.setUniform("posOffset", pos);

		//Selecting Shape
		if (selectedNum == 1) 
		{
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		else if (selectedNum == 2)
		{
			glBindVertexArray(vao2);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
		else if (selectedNum == 3)
		{
			glBindVertexArray(vao3);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(pWindow);
	}

	//clean program
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
	return 0;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // clockwise order
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		selectedNum = 1;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		selectedNum = 2;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		selectedNum = 3;
	}
}

void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); //return the number of second since GLFW started, as double.

	elapsedSeconds = currentSeconds - previousSeconds;
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed << APP_TITLE << " FPS: " << fps << " Frame Time: " << msPerFrame << "(ms)";

		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}

bool initOpenGL()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		system("pause");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (gFullscreen)
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);

		if (pVmode != NULL)
		{
			pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
		}
	}
	else
	{
		pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	}

	if (pWindow == NULL)
	{
		std::cerr << "Failed to create window" << std::endl;

		glfwTerminate();

		system("pause");
		return false;
	}

	glfwMakeContextCurrent(pWindow);

	glfwSetKeyCallback(pWindow, glfw_onKey);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;

		glfwTerminate();

		system("pause");
		return false;
	}

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	return true;
}
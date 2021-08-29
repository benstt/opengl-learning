// https://learnopengl.com/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader-lesson-1.4/Shader.h"

void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	// initialize GLFW
	glfwInit();
	// set version and core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	// set callback to handle when window is resized
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// initialize vertex and fragment shaders
	Shader shader("shader-lesson-1.4/les1.4-vShader.vs",
		"shader-lesson-1.4/les1.4-fShader.fs");

	// positions and colors
	float vertices[] = {
		// positions         // colors
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // top
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // bottom right
	};

	// indices for te EBO. this will determine which vertex to draw first
	unsigned int indices[] = {
		3, 2, 0,  // first triangle
		2, 0, 1   // second triangle
	};

	// generate a vertex buffer object and a vertex array object
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the VAO. any subsequent VBO, EBO, 
	// glVertex... glEnable... calls will be stored in this VAO.
	glBindVertexArray(VAO);

	// bind the buffer to an array buffer and assign the vertices to it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// bind the buffer to an element array buffer and assign the indices to it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// tell OpenGL how should it operate with the vertex data
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// set wireframe mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// use shader
		shader.use();
		// Exercise 2: move the triangle by an offset uniform
		// shader.setFloat("xOffset", 0.5f);
		// shader.setFloat("yOffset", 0.5f);

		// draw triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// deallocate objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// whenever the window is resized this function gets called
void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	// tell OpenGL the size of the window
	glViewport(0, 0, width, height);
}

// react to key presses
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
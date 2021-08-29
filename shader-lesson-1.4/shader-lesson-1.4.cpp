// https://learnopengl.com/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// shaders
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n";

const char* exFragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\n";

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

	// create vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// attach the source code to the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for errors on the vertex shader
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	// create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach the source code to the shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for errors on the fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::DEF_FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	// exercise 3 fragment shader
	unsigned int exFragmentShader;
	exFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(exFragmentShader, 1, &exFragmentShaderSource, NULL);
	glCompileShader(exFragmentShader);

	glGetShaderiv(exFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(exFragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::EX_FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	// create default and excercise 3 programs
	unsigned int shaderProgram, exProgram;
	shaderProgram = glCreateProgram();
	exProgram = glCreateProgram();

	// link the shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// link the shaders to the excercise 3 program
	// using a different fragment shader
	glAttachShader(exProgram, vertexShader);
	glAttachShader(exProgram, exFragmentShader);
	glLinkProgram(exProgram);

	// check for errors on the linking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::DEFAULT_PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
	}

	// also check erros for exercise 3 program
	glGetProgramiv(exProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(exProgram, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::EXERCISE_PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
	}

	// once all the shaders have been assigned to the program, delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// also delete exercise 3 shader
	glDeleteShader(exFragmentShader);

	/* Tests
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	

	float rectangleVertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f  // top left
	};

	// Exercise 1: Draw two triangles, one next to each other.
	float triangleVertices[] = {
		// first triangle
		-1.0f, -1.0f, 0.0f,
		-0.5f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		// second triangle
		0.0f, 1.0f, 0.0f,
		0.5f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};
	*/

	// left triangle
	float exVerticesT1[] = {
		-1.0f, -1.0f, 0.0f,
		-0.5f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	};

	// right triangle
	float exVerticesT2[] = {
		0.0f, 1.0f, 0.0f,
		0.5f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
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

	// bind the buffer to an array buffer and assign the vertices to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(exVerticesT1), exVerticesT1, GL_STATIC_DRAW);

	// bind the buffer to an element array buffer and assign the indices to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// tell OpenGL how should it operate with the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Exercise 2: Generate two triangles using different VAOs and VBOs
	unsigned int exVAO, exVBO;
	glGenVertexArrays(1, &exVAO);
	glGenBuffers(1, &exVBO);

	glBindVertexArray(exVAO);

	glBindBuffer(GL_ARRAY_BUFFER, exVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(exVerticesT2), exVerticesT2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

		// draw triangle and use default program
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw second triangle and use exercise 3 program
		glUseProgram(exProgram);
		glBindVertexArray(exVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// deallocate objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// also delete exercise 3 array and buffer
	glDeleteVertexArrays(1, &exVAO);
	glDeleteBuffers(1, &exVBO);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(exProgram);

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
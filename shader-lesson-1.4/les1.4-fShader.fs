#version 330 core
out vec4 FragColor;

in vec3 ourPos;
in vec3 ourColor;

void main()
{
	FragColor = vec4(ourColor, 1.0f);

	// Exercise 3: set the fragment's color to the vertex position
	// FragColor = vec4(ourPos, 1.0f);
}
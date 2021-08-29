#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// out vec3 ourPos;
out vec3 ourColor;

uniform float xOffset;
uniform float yOffset;

void main() 
{
	// Exercise 1: set the triangle upside down
	// gl_Position = vec4(-aPos, 1.0f);

	// Exercise 2: move the triangle by an offset uniform
	gl_Position = vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0f);
	// Exercise 3: set the fragment's color to this position
	// ourPos = aPos;
	ourColor = aColor;
}
#version 330 core
out vec4 FragColor;

in vec3 ourPos;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float percentage;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), percentage);

	// Exercise 3: set the fragment's color to the vertex position
	// FragColor = vec4(ourPos, 1.0f);
}
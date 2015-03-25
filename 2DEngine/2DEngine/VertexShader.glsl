#version 330

in vec2 position;
in vec4 colour;
in vec2 vertexUV;

uniform mat4 MVP;

out vec4 vertColour;
out vec2 UV;

void main()
{
	vertColour = colour;
	UV = vertexUV;

	gl_Position = MVP * vec4(position, 0, 1);
}
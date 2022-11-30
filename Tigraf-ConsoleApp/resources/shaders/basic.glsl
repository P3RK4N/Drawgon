$VertexShader
#version 460 core

layout (location = 0) in vec3 ObjectPosition;
layout (location = 1) in vec3 Color;

uniform mat4 VP;

out vec4 bCol;

void main()
{
	gl_Position = VP * vec4(ObjectPosition, 1.0);
	bCol = vec4(Color,1.0);
}

$PixelShader
#version 460 core

in vec4 bCol;

out vec4 FragColor;

void main()
{
   FragColor = bCol;
}
$VertexShader
#version 460 core

layout (location = 0) in vec3 ObjectPositionCS;
layout (location = 1) in vec3 Color;

out vec4 bCol;

void main()
{
	gl_Position = vec4(ObjectPositionCS, 1.0);
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
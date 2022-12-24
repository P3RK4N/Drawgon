$VertexShader
#version 460 core

layout (location = 0) in vec3 ObjectPosition;

uniform mat4 VP;

void main()
{
	gl_Position = VP * vec4(ObjectPosition, 1.0);
}

$PixelShader
#version 460 core

out vec4 FragColor;

void main()
{
   FragColor = vec4(0.3, 1.0, 1.0, 1.0);
}
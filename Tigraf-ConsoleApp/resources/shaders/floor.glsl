$VertexShader
#version 460 core

layout (location = 0) in vec3 ObjectPosition;

uniform mat4 VP;
uniform mat4 M;

out vec4 fWorldPosition;

void main()
{
	fWorldPosition = M * vec4(ObjectPosition, 1.0) / 4;
	gl_Position = VP * M * vec4(ObjectPosition, 1.0);
}

$PixelShader
#version 460 core

in vec4 fWorldPosition;

out vec4 FragColor;

void main()
{
	float floorX = fract(fWorldPosition.x);
	float floorZ = fract(fWorldPosition.z);

	float val = (floorX < 0.5 && floorZ < 0.5) || (floorX > 0.5 && floorZ > 0.5) ? 0.8 : 0.15;
	FragColor = vec4(val, val, val, 1.0);
}
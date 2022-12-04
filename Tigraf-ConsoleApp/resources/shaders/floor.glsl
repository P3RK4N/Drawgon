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
#extension GL_ARB_bindless_texture : require

layout (std140, binding = 0) uniform BufferTexture2D
{
	sampler2D textureHandle[2];
};

in vec4 fWorldPosition;

out vec4 FragColor;

void main()
{
	float floorX = fract(fWorldPosition.x);
	float floorZ = fract(fWorldPosition.z);

	vec2 coords = vec2(floorX, floorZ);

	float val = ((floorX < 0.5 && floorZ < 0.5) || (floorX > 0.5 && floorZ > 0.5) ? 1.8 : 0.4);

	FragColor = vec4(val, val, val, 1.0);// * texture(textureHandle[1], coords * 2.0);
}
$VertexShader
#version 460 core


layout (location = 0) in vec3 ObjectPositionVS;

uniform mat4 VP;
uniform mat4 M;

out vec4 WorldPositionPS;
out vec3 ObjectPositionPS;

void main()
{
	WorldPositionPS = M * vec4(ObjectPositionVS, 1.0);
	ObjectPositionPS = ObjectPositionVS;
	gl_Position = VP * M * vec4(ObjectPositionVS, 1.0);
}



$PixelShader
#version 460 core
#extension GL_ARB_bindless_texture : require

layout(std140, binding = 0) uniform TextureBuffer
{
	sampler2D textures2D[100];
	sampler3D textures3D[20];
	samplerCube texturesCube[20];
};

in vec4 WorldPositionPS;
in vec3 ObjectPositionPS;

out vec4 FragColor;

void main()
{
	float floorX = fract(WorldPositionPS.x / 4);
	float floorZ = fract(WorldPositionPS.z / 4);

	float val = ((floorX < 0.5 && floorZ < 0.5) || (floorX > 0.5 && floorZ > 0.5) ? 1.8 : 0.4);

	float dist = length(ObjectPositionPS) / 20;
	float opacity = mix(1.0, 0.0, dist*dist);
	FragColor = vec4(val, val, val, opacity);
}
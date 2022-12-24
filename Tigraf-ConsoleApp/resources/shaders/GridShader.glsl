$VertexShader
#version 460 core


layout (location = 0) in vec3 ObjectPositionVS;

layout(std140, binding = 1) uniform PerFrameBuffer
{
	mat4 VP;
	vec3 CameraWorldPosition;
};

layout(std140, binding = 2) uniform PerModelBuffer
{
	mat4 M;
	mat4 MVP;
};

out vec4 WorldPositionPS;
out vec3 ObjectPositionPS;

void main()
{
	WorldPositionPS = vec4(ObjectPositionVS, 0.0) + vec4(CameraWorldPosition.x, 0.0, CameraWorldPosition.z, 1.0);
	ObjectPositionPS = ObjectPositionVS;

	gl_Position = VP * WorldPositionPS;
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
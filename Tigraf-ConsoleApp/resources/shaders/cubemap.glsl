$VertexShader
#version 460 core


layout (location = 0) in vec3 ObjectPosition;
layout(location = 1) in vec2 TextureCoordinateVS;

uniform mat4 MVP;

out vec2 TextureCoordinatePS;

void main()
{
	TextureCoordinatePS = TextureCoordinateVS;
	gl_Position = MVP * vec4(ObjectPosition, 1.0);
}



$PixelShader
#version 460 core
#extension GL_ARB_bindless_texture : require

layout (std140, binding = 0) uniform BufferTexture2D
{
	sampler2D textureHandle[2];
};

in vec2 TextureCoordinatePS;

out vec4 FragColor;

void main()
{
	FragColor = texture(textureHandle[0], TextureCoordinatePS);
}
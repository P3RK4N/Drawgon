#pragma once
#include <glm/glm.hpp>


class SceneData
{
public:
	struct PerFrameData
	{
		glm::mat4 CameraViewProjection{};
		glm::vec3 CameraWorldPosition{};
		float TotalTime;
		float FrameTime;
		uint32_t SkyboxIndex;
	};

	struct PerModelData
	{
		glm::mat4 M{};
		glm::mat4 MVP{};
	};

	PerFrameData m_PerFrameData;
	PerModelData m_PerModelData;
};
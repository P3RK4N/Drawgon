#pragma once
#include <Tigraf/Renderer/Camera/Camera.h>
#include <Tigraf/Core/Timer.h>

namespace Tigraf
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera
		(
			float aspectRatio, 
			float nearPlane, 
			float farPlane, 
			const glm::vec3& position = { 0, 1, -2 },
			const glm::vec3& forward = { 0, 0, 1 }, 
			const glm::vec3& up = { 0, 1, 0 },
			float FOV = 45.0f
		);
		SceneCamera
		(
			std::pair<int, int> windowSize, 
			float nearPlane, 
			float farPlane, 
			const glm::vec3& position = { 0, 1, -2 },
			const glm::vec3& forward = { 0, 0, 1 }, 
			const glm::vec3& up = { 0, 1, 0 },
			float FOV = 45.0f
		);

		virtual ~SceneCamera();

		virtual void onUpdate(const TimeStep& ts) override;

		void setInteractable(bool interactable) { m_Interactable = interactable; }
		const bool isInteractable() { return m_Interactable; }

	private:
		void updateTransform(const TimeStep& ts);

		float m_MoveSpeed = 10.0f;
		float m_RotateSpeed = 20.0f;

		bool m_Interactable = false;
	};
}

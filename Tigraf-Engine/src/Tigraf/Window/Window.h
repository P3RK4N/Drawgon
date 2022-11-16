#pragma once
#include "Tigraf/Core/Core.h"
#include "Tigraf/Event/Event.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>

namespace Tigraf
{
	class Window
	{
	public:
		Window() = default;
		virtual ~Window() {}

		virtual std::pair<int, int> getSize() = 0;
		virtual void* getWindowHandle() = 0;

		bool isVsyncEnabled() { return m_WindowData.m_Vsync;}
		virtual void setVsync(bool enableVsync) { m_WindowData.m_Vsync = enableVsync; }

		virtual void onUpdate() {}

	public:
		static Scope<Window> createWindow
		(
			int width = 1280, 
			int height = 720, 
			const char* name = "Tigraf", 
			bool enableVsync = true, 
			std::function<void(Event&)> eventCallback = [](Event& e) { return; }
		);

	protected:

		struct WindowData
		{
			bool m_Vsync = true;
			std::function<void(Event&)> m_EventCallback = nullptr;
		};

		WindowData m_WindowData{};

		virtual void setEventCallbacks() {}
	};
}
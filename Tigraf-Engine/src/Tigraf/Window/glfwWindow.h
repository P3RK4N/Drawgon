#pragma once
#include "Window.h"

namespace Tigraf
{
	class glfwWindow : public Window
	{
	public:
		glfwWindow(int width, int height, const char* name, bool vsyncEnabled, std::function<void(Event&)> eventCallback);
		virtual ~glfwWindow();

		virtual std::pair<int, int> getSize() override;
		virtual void* getWindowHandle() override { return (void*)m_WindowHandle; }

		virtual void setVsync(bool vsyncEnabled) override { Window::setVsync(vsyncEnabled); glfwSwapInterval(vsyncEnabled); }

		virtual void onUpdate() override { glfwSwapBuffers(m_WindowHandle); glfwPollEvents(); }

	protected:
		GLFWwindow* m_WindowHandle = nullptr;

		virtual void setEventCallbacks() override;

	private:
		static void onError(int error, const char* description);
	};
}
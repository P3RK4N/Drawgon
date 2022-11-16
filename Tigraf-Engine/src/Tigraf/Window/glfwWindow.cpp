#include "PCH.h"
#include "glfwWindow.h"

namespace Tigraf
{
	glfwWindow::glfwWindow(int width, int height, const char* name, bool vsyncEnabled, std::function<void(Event&)> eventCallback)
	{
		TIGRAF_ASSERT(glfwInit(), "GLFW library couldn't be initialized!");
		glfwSetErrorCallback(glfwWindow::onError);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
		TIGRAF_ASSERT(window, "Window creation failed!");

		glfwMakeContextCurrent(window);
		glfwSwapInterval(vsyncEnabled);

		this->m_WindowHandle = window;
		this->m_WindowData.m_Vsync = vsyncEnabled;
		this->m_WindowData.m_EventCallback = eventCallback;

		glfwSetWindowUserPointer(m_WindowHandle, &m_WindowData);

		setEventCallbacks();
	}

	glfwWindow::~glfwWindow()
	{
		glfwDestroyWindow(m_WindowHandle);
		m_WindowHandle = nullptr;
		glfwTerminate();
	}

	std::pair<int,int> glfwWindow::getSize()
	{
		int width, height;
		glfwGetWindowSize(m_WindowHandle, &width, &height);
		return { width,height };
	}

	void glfwWindow::onError(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	void glfwWindow::setEventCallbacks()
	{
		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
		{
			ResizeData data{ width, height };
			Event e{EVENT_TYPE::RESIZE, (void*)&data};
			
			WindowData* wd = (WindowData*)glfwGetWindowUserPointer(window);
			wd->m_EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
		{
			Event e{EVENT_TYPE::CLOSE, nullptr};
			
			WindowData* wd = (WindowData*)glfwGetWindowUserPointer(window);
			wd->m_EventCallback(e);
		});

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			EVENT_TYPE et;

			switch(action)
			{
			case GLFW_PRESS:
				et = EVENT_TYPE::KEY_PRESS;
				break;
			case GLFW_RELEASE:
				et = EVENT_TYPE::KEY_RELEASE;
				break;
			case GLFW_REPEAT:
				et = EVENT_TYPE::KEY_REPEAT;
			}

			KeyData data{ key };
			Event e{ et, (void*)&data };
			WindowData* wd = (WindowData*)glfwGetWindowUserPointer(window);
			wd->m_EventCallback(e);
		});
	}
}
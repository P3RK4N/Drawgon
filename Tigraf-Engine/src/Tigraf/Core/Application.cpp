#include "PCH.h"
#include "Application.h"

#include "Tigraf/Window/Window.h"

namespace Tigraf
{
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification spec)
		: m_ApplicationSpecification(spec)
	{
		if(s_Instance != nullptr) delete s_Instance;
		s_Instance = this;
	}

	Application::~Application()
	{
		CORE_INFO("Shutting down");
		s_Instance = nullptr;
		m_Window.reset();
	}

	void Application::init()
	{
		m_Window = Window::createWindow(1280, 720, "Tigraf", true, BIND_EVENT_FN(Application::onEvent));
	}

	void Application::run()
	{
		const auto& [x, y] = m_Window->getSize();
		glViewport(0, 0, x, y);
		gladLoadGL();
		while(m_Running) 
		{
			glClear(GL_COLOR_BUFFER_BIT);		
			m_Window->onUpdate();
		}
	}

	void Application::onEvent(Event& event)
	{
		DISPATCH(EVENT_TYPE::RESIZE, event, Application::onResize);
		DISPATCH(EVENT_TYPE::CLOSE, event, Application::onClose);
		DISPATCH(EVENT_TYPE::KEY_PRESS, event, Application::onKey);
	}

	bool Application::onResize(void* eventData)
	{
		ResizeData* data = (ResizeData*)eventData;
		CORE_TRACE(*data);
		return false;
	}

	bool Application::onClose(void* eventData)
	{
		CORE_TRACE("CloseEvent");
		m_Running = false;
		return false;
	}

	bool Application::onKey(void* eventData)
	{
		KeyData* data = (KeyData*)eventData;
		CORE_TRACE(*data);
		return false;
	}
}
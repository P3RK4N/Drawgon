#include "PCH.h"
#include "Application.h"

namespace Tigraf
{
	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification spec)
		: m_ApplicationSpecification(spec)
	{
		
	}

	Application::~Application()
	{
		CORE_INFO("Shutting down");
		s_Instance = nullptr;
	}

	void Application::run()
	{
	}

}
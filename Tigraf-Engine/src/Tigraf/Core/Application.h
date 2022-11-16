#pragma once
#include "Tigraf/Window/Window.h"
#include "Tigraf/Event/Event.h"

namespace Tigraf
{
	struct CommandLineArgs
	{
		int argc = 0;
		char** argv = nullptr;
	};

	struct ApplicationSpecification
	{
		std::string name{};
		std::filesystem::path workingDirectory{};
		CommandLineArgs args{};
	};



	class Application
	{
	public:
		Application(ApplicationSpecification spec);
		virtual ~Application();

		void init();
		void run();

		std::string getName() { return m_ApplicationSpecification.name; }
		std::filesystem::path getWorkingDirectory() { return m_ApplicationSpecification.workingDirectory; }

	public:
		static Application* s_Instance;

	protected:
		void onEvent(Event& event);
		EVENT(onResize);
		EVENT(onClose);
		EVENT(onKey);

	protected:
		ApplicationSpecification m_ApplicationSpecification{};
		bool m_Running = true;

		Scope<Window> m_Window = nullptr;


	private:

	};
}
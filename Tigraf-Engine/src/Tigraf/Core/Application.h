#pragma once

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
		~Application();

		void run();

		std::string getName() { return m_ApplicationSpecification.name; }
		std::filesystem::path getWorkingDirectory() { return m_ApplicationSpecification.workingDirectory; }

	protected:
		ApplicationSpecification m_ApplicationSpecification{};
		static Application* s_Instance;

	private:

	};
}
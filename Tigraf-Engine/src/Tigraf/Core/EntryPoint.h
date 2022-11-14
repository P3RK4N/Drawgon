#pragma once
#include "Tigraf/Core/Core.h"
#include "Tigraf/Core/Application.h"

#include <iostream>

#ifdef TIGRAF_WINDOWS
#include <windows.h>

int main(int argc, char** argv)
{
	Tigraf::Log::init();
	CORE_INFO("Tiny Graphic Framework!");

	auto app = new Tigraf::Application(Tigraf::ApplicationSpecification{ "Tiny Graphic FrameWork", std::filesystem::current_path(), { argc, argv } });
	TIGRAF_ASSERT(app, "App creation was unsuccessful");

	app->run();

	delete app;

	std::cin.get();
}

#endif
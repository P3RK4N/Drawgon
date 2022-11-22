#pragma once
#include <GLFW/glfw3.h>

#include "Tigraf/Core/Application.h"

namespace Tigraf
{
	class glfwInput
	{
		bool isKeyPressed(int keycode)	{	return glfwGetKey((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), keycode) == GLFW_PRESS;		}
		bool isKeyReleased(int keycode)	{	return glfwGetKey((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), keycode) == GLFW_RELEASE;	}
		bool isKeyHeld(int keycode)		{	return glfwGetKey((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), keycode) == GLFW_REPEAT;	}
	};
}
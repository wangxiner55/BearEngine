#include "Application.h"


#include "Events/ApplicationEvent.h"
#include "log.h"



namespace BEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		std::cout << "Hello World" << std::endl;
	}
}

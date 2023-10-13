#pragma once
#include "Core.h"

namespace BEngine
{
	class BEAR_API Application
	{
	public:

		Application();
		~Application();

		void Run();

	};


	Application* CreateApplication();

}

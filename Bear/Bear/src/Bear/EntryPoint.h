#pragma once
#ifdef BR_PLATFORM_WINDOWS
extern BEngine::Application* BEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = BEngine::CreateApplication();
	app->Run();
	delete app;
	getchar();
}

#endif // BR_PLATFORM_WINDOWS

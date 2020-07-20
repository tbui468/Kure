#pragma once

#ifdef KR_PLATFORM_WINDOWS

//extern will be found somewhere else (where???)
extern Kure::Application* Kure::CreateApplication();

int main(int argc, char** argv) {
	Kure::Log::Init();
	//Kure::Log::GetCoreLogger()->warn("initialized log");
	//Kure::Log::GetClientLogger()->info("Hellow");
	KR_CORE_WARN("Initialized log testing!!!");
	int a = 10;
	KR_INFO("Hellow Var={0}", a);

	Kure::Application* app = Kure::CreateApplication();
	app->Run();
	delete app;
}
#endif

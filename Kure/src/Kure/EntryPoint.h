#pragma once

#ifdef KR_PLATFORM_WINDOWS


extern Kure::Application* Kure::CreateApplication(); //defined in SandboxApp.cpp

int main(int argc, char** argv) {
	Kure::Log::Init();
	KR_CORE_WARN("Initialized log testing!!!");
	int a = 10;
	KR_INFO("Hellow Var={0}", a);
	auto app = Kure::CreateApplication();
	app->Run();
	delete app;
}
#endif

#pragma once

#ifdef KR_PLATFORM_WINDOWS


extern Kure::Application* Kure::CreateApplication(); //defined in SandboxApp.cpp, which is our client 

int main(int argc, char** argv) {
	Kure::Log::Init();
	KR_CORE_WARN("Initialized log testing!!!");
	int a = 10;
	KR_INFO("Hellow Var={0}", a);
	Kure::Application* app = Kure::CreateApplication(); 
	app->Run(); //this is the main game loop
	delete app;
}
#endif

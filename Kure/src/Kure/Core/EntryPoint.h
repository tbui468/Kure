#pragma once

#ifdef KR_PLATFORM_WINDOWS


extern Kure::Application* Kure::CreateApplication(); //defined in SandboxApp.cpp, which is our client 

int main(int argc, char** argv) {
	Kure::Log::Init();
	Kure::Application* app = Kure::CreateApplication(); 
	app->Run(); 
	delete app;
}

#endif

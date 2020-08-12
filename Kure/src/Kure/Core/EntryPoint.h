#pragma once

#ifdef KR_PLATFORM_WINDOWS


extern Kure::Application* Kure::CreateApplication(); //defined in SandboxApp.cpp, which is our client 

int main(int argc, char** argv) {
	Kure::Log::Init();

	KR_PROFILE_BEGIN_SESSION("Startup", "KureProfile-Startup.json");
	Kure::Application* app = Kure::CreateApplication(); 
	KR_PROFILE_END_SESSION();

	KR_PROFILE_BEGIN_SESSION("Runtime", "KureProfile-Runtime.json");
	app->Run(); 
	KR_PROFILE_END_SESSION();

	KR_PROFILE_BEGIN_SESSION("Shutdown", "KureProfile-Shutdown.json");
	delete app;
	KR_PROFILE_END_SESSION();
}

#endif

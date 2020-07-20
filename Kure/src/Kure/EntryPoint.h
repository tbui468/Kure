#pragma once

#ifdef KR_PLATFORM_WINDOWS

//extern will be found somewhere else (where???)
extern Kure::Application* Kure::CreateApplication();

int main(int argc, char** argv) {
	Kure::Application* app = Kure::CreateApplication();
	app->Run();
	delete app;
}
#endif

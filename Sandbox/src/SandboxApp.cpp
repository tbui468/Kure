#include <Kure.h>

class Sandbox : public Kure::Application
{
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

Kure::Application* Kure::CreateApplication() {
	return new Sandbox();
}

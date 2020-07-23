#include <Kure.h> //this is all the game engine header files


class ExampleLayer : public Kure::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {
		KR_TRACE("ExampleLayer:OnUpdate()");
	}

	void OnEvent(Kure::Event& event) override {
		KR_INFO("{0}", event);
	}
};

//class for our app, which is a child class of Kure::Application
class Sandbox : public Kure::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};

//create new instance of our app
Kure::Application* Kure::CreateApplication() {
	return new Sandbox();
}

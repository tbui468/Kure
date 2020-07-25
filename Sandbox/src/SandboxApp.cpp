#include <Kure.h> //this is all the game engine header files


class ExampleLayer : public Kure::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {
//		KR_TRACE("ExampleLayer:OnUpdate()");
	}

	void OnEvent(Kure::Event& event) override {
//		KR_INFO("{0}", event);
		if (event.GetEventType() == Kure::EventType::KeyPressed)
		{
			Kure::KeyPressedEvent* e = (Kure::KeyPressedEvent*) & event;
			KR_INFO("THis key pressed: {0}", char(e->GetKeyCode()));
		}

		if (event.GetEventType() == Kure::EventType::MouseButtonPressed) {
			Kure::MouseButtonPressedEvent* e = (Kure::MouseButtonPressedEvent*) & event;
			KR_INFO("THis key pressed: {0}", char(e->GetMouseButton()));
		}
	}
};

//class for our app, which is a child class of Kure::Application
class Sandbox : public Kure::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Kure::ImGuiLayer());
	}
	~Sandbox() {

	}
};

//create new instance of our app
Kure::Application* Kure::CreateApplication() {
	return new Sandbox();
}

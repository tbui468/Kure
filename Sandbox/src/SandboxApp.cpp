#include <Kure.h> //this is all the game engine header files
#include "Kure/Core/EntryPoint.h"

#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"



class Sandbox : public Kure::Application
{
public:
	Sandbox() {
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {

	}
};

Kure::Application* Kure::CreateApplication() {
	return new Sandbox();
}

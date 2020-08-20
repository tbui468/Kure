#include <Kure.h> //this is all the game engine header files
#include "Kure/Core/EntryPoint.h"

#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace Kure {

	class KureEditor : public Application
	{
	public:
		KureEditor() : Application("Kure Editor") {
			PushLayer(new EditorLayer());
		}
		~KureEditor() {

		}
	};

	Application* CreateApplication() {
		return new KureEditor();
	}

}

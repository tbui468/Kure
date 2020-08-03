#include "krpch.h"
#include "OrthographicCamera.h"

namespace Kure {


	Ref<Camera> Camera::Create(float left, float right, float bottom, float top, float n, float f) {
		return std::make_shared<OrthographicCamera>(left, right, bottom, top, n, f);
	}

}
#include "krpch.h"
#include "OrthographicCamera.h"

namespace Kure {


	Camera* Camera::Create(float left, float right, float bottom, float top, float n, float f) {
		return new OrthographicCamera(left, right, bottom, top, n, f);
	}

}
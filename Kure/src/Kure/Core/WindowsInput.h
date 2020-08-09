#pragma once

#include "Input.h"

namespace Kure {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int key) const override;
		virtual bool IsButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> GetMousePositionImpl() const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;
	};

}


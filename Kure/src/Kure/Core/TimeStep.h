#pragma once

namespace Kure {
	class TimeStep {
	public:
		TimeStep(float time = 0.0f) :m_Time(time) {}
		operator float() const { return m_Time; } //can treat TimeStep object like any float (eg for multiplication)
		inline float GetSeconds() { return m_Time; }
		inline float GetMilliseconds() { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}

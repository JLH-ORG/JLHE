#pragma once

namespace JLHE {
	
	class Timestep {
	public:
		Timestep(float time)
			: m_Time(time) {}

		operator float() { return m_Time; }

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return m_Time * 1000; }
	private:
		float m_Time;
	};
}
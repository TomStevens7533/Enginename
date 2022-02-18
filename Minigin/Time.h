#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae {
	class Time : public Singleton<Time>
	{
	public:
		Time();
		~Time() = default;

		float GetDeltaTime();
		void Update();
	private:
		std::chrono::steady_clock::time_point  m_StartTime;
		float m_DeltaTime;
	};
}

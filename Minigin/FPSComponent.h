#pragma once
#include "BaseComponent.h"

namespace dae {
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent() = default;

		inline static const int GetComponentID() { return m_ComponentContext.m_ComponentID; }
		inline static void SetComponentID(int newID) {
			m_ComponentContext.m_ComponentID = newID;
			m_ComponentContext.isRegistered = true;
		}

		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		const int GetFpsCount() const { return m_fps; }


	private:
		static ComponentContext m_ComponentContext;
		int m_fps;
		int m_fpscount;
		std::chrono::steady_clock::time_point  m_StartTime;
		bool m_IsFirstRun = true;

	};
}



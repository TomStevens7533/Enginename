#pragma once
#include "BaseComponent.h"

namespace dae {
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent() = default;

		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		const int GetFpsCount() const { return m_fps; }


	private:
		int m_fps;
		int m_fpscount;
		float m_TimePassed = 0.f;

	};
}



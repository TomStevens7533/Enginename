#include "MiniginPCH.h"

#include "FPSComponent.h"
#include <sysinfoapi.h>

#include <iostream>



namespace dae {


	ComponentContext FPSComponent::m_ComponentContext = ComponentContext{ false,  INT_MAX };

	FPSComponent::FPSComponent() : m_fpscount{0}, m_fps{0}
	{


	}

	void FPSComponent::Render() const
	{

	}

	void FPSComponent::Update()
	{
		if (m_IsFirstRun) {
			m_StartTime = std::chrono::high_resolution_clock::now();
			m_IsFirstRun = false;
			return;
		}

		m_fpscount++;
		float timePassed = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - m_StartTime).count();
		if (timePassed > 0.25 && m_fpscount > 10) {
			//1 sec has passed
			m_fps = static_cast<int>(static_cast<float>(m_fpscount) / timePassed);

			//reset counter
			m_fpscount = 0;
			m_StartTime = std::chrono::high_resolution_clock::now();
			std::cout << m_fps << std::endl;
		}

	}

	void FPSComponent::LateUpdate()
	{

	}


}
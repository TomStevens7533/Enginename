#pragma once
#pragma once
#include <vector>

#include "Layer.h"

namespace dae
{
	class  Thrashlayer : public Layer
	{
	public:
		Thrashlayer();
		~Thrashlayer();



		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;


		void Begin();
		void End();

	private:
		std::vector<float> m_ThrashCachMeasurments;
	};


}

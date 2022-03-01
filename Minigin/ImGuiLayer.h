#pragma once
#include "Layer.h"

namespace dae
{
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();



		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;


		void Begin();
		void End();


	};


}

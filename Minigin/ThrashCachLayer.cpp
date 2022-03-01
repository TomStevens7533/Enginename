#pragma once
#include "ThrashCachLayer.h"

#include <chrono>

#include "imgui_plot.h"
#include "MiniginPCH.h"
#include "Minigin.h"
#include <algorithm>




namespace dae
{
	std::vector<float> ThrashCach2();
	std::vector<float> ThrashCach1();


	Thrashlayer::Thrashlayer()
		: Layer("ImGuiLayer")
	{

	}
	Thrashlayer::~Thrashlayer()
	{

	}


	void Thrashlayer::OnAttach()
	{

	


	}
	void Thrashlayer::OnDetach()
	{
		
	}

	void Thrashlayer::Begin()
	{
		
	}
	void Thrashlayer::End()
	{
		
	}

	void Thrashlayer::OnImGuiRender()
	{

		ImGui::PlotConfig confex2;

		;
		confex2.tooltip.format = "x=%.2f, y=%.2f";
		confex2.grid_x.show = true;
		confex2.grid_y.show = true;
		confex2.frame_size = ImVec2(200, 200);
		confex2.line_thickness = 3.f;


		ImGui::ShowDemoWindow();

		ImGui::Begin("Profiling");
		if(ImGui::Button("Run Trash the cache ex2"))
		{
			
			m_ThrashCachMeasurments	 = ThrashCach2();
			
		
		}
		if (ImGui::Button("Run Trash the cache ex1"))
		{

			m_ThrashCachMeasurments = ThrashCach1();


		}
		if(m_ThrashCachMeasurments.size() > 0)
		{
			confex2.scale.min = 0.f;
			confex2.scale.max = *std::max_element(m_ThrashCachMeasurments.begin(), m_ThrashCachMeasurments.end());
			confex2.tooltip.show = true;
			confex2.values.ys = m_ThrashCachMeasurments.data();
			confex2.values.count = static_cast<int>(m_ThrashCachMeasurments.size());
			ImGui::Text("Element amount: ");
			ImGui::Text(std::to_string(m_ThrashCachMeasurments.size()).c_str());
			ImGui::Plot("plot", confex2);
		}
		//viewport
		ImGui::End();


		
	}
	struct Transform
	{
		float matrix[16]
		{
			1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1
		};
	};
	class GameObjet3D
	{
	public:
		Transform* trans;
		int ID;
	};

	std::vector<float> ThrashCach2()
	{
		std::vector<float> timeVector;
		std::vector<GameObjet3D*> intVec;
		intVec.reserve(1024 * 1024);
		for (int i = 0; i < intVec.capacity(); ++i)
			intVec.push_back(new GameObjet3D());

		for (int stepSize = 1; stepSize <= 1024;)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 1; i < intVec.size(); i += stepSize)
			{
				intVec[i]->ID *= 2;
			}
			auto endTime = std::chrono::high_resolution_clock::now();

			float deltaTime = std::chrono::duration<float>(endTime - startTime).count();

			timeVector.push_back(deltaTime);
			stepSize = stepSize * 2;
		}

		for (int i = 0; i < intVec.size(); ++i)
		{
			delete intVec[i];
		}

		return  timeVector;
	}

	std::vector<float> ThrashCach1()
	{
		std::vector<float> timeVector;
		std::vector<int*> intVec;
		intVec.reserve(1024 * 1024);
		for (int i = 0; i < intVec.capacity(); ++i)
			intVec.push_back(new int);

		for (int stepSize = 1; stepSize <= 1024;)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 1; i < intVec.size(); i += stepSize)
			{
				*intVec[i] *= 2;
			}
			auto endTime = std::chrono::high_resolution_clock::now();

			float deltaTime = std::chrono::duration<float>(endTime - startTime).count();

			timeVector.push_back(deltaTime);
			stepSize = stepSize * 2;
		}

		for (int i = 0; i < intVec.size(); ++i)
		{
			delete intVec[i];
		}

		return  timeVector;
	}
}

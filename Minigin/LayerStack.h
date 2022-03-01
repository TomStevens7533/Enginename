#pragma once

#pragma once

#include <memory>

#include "Layer.h"

#include <vector>

namespace dae {

	class  LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(std::string& layerName);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerIndex = 0;
	};
}
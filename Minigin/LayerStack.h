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

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.cbegin(); }
		std::vector<Layer*>::const_iterator end() const  { return m_Layers.cend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerIndex = 0;
	};
}
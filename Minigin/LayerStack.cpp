#include "MiniginPCH.h"
#include "LayerStack.h"

namespace dae
{

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
	}


	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;

		}
	}

	void LayerStack::PopLayer(std::string& layerName)
	{
		auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&layerName](auto layerPtr)
		{
				return layerPtr->GetLayerName() == layerName;
		});
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerIndex--;
		}
	}

}

#include "MiniginPCH.h"
#include "Layer.h"

namespace dae {


	Layer::Layer(const std::string& name)
		: m_LayerName(name)
	{
	}

	Layer::~Layer()
	{

	}

	void Layer::Add(const std::shared_ptr<SceneObject>& object)
	{
		m_Objects.push_back(object);
	}
}

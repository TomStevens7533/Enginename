#pragma once
#include <string>


namespace dae {

	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetLayerName() const { return  m_LayerName; };

	protected:
		std::string m_LayerName;
	};
}

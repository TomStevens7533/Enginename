#pragma once
#include <string>
#include <memory>
#include <vector>
#include "SceneObject.h"


namespace dae {

	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		void Add(const std::shared_ptr<SceneObject>& object);


		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnFixedUpdate() {}
		virtual void OnLateUpdate() {}

		const std::vector < std::shared_ptr<SceneObject>>& GetLayerObjects() const { return m_Objects; }
		virtual void OnImGuiRender() const {}

		inline const std::string& GetLayerName() const { return  m_LayerName; };

	protected:
		std::string m_LayerName;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

	};
}

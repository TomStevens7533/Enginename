#pragma once
#include "BaseComponent.h"
#include <unordered_map>

namespace dae 
{

	class EntityManager //TODO: change to use an unordered map instead
	{
	public:
		EntityManager() = default;
		~EntityManager();


		template<class TComponent>
		bool AddComponent(std::shared_ptr<BaseComponent>& component)
		{
			if (m_ComponentMap.contains(TComponent::GetComponentID())) //return false if map already contains component
				return false;
			m_ComponentMap.insert(std::make_pair(TComponent::GetComponentID(), component));
			return true;
		}

		template<class TComponent>
		bool RemoveComponent() 
		{
			if (m_ComponentMap.erase(TComponent::GetComponentID()) == 0)
				return false;
			else
				return true;
		}

		template<class TComponent>
		std::shared_ptr<TComponent> GetComponent()
		{
			if (m_ComponentMap.contains(TComponent::GetComponentID())) {
				return dynamic_pointer_cast<TComponent>(m_ComponentMap[TComponent::GetComponentID()]);
			}
			return nullptr;
		}


		void Update();
		void LateUpdate();
		void Render() const;
	private:
		std::unordered_map<int, std::shared_ptr<BaseComponent>> m_ComponentMap;
		int m_ComponentsRegistered = 0;
	};
}




#pragma once
#include <map>
#include "BaseComponent.h"

namespace dae 
{

	class EntityManager
	{
	public:
		EntityManager() = default;
		~EntityManager();


		template<class TComponent>
		bool AddComponent(BaseComponent* component)
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
		TComponent * const GetComponent()
		{
			if (m_ComponentMap.contains(TComponent::GetComponentID())) {
				return dynamic_cast<TComponent*>(m_ComponentMap[TComponent::GetComponentID()]);
			}
			return nullptr;
		}


		void Update();
		void LateUpdate();
		void Render() const;
	private:
		std::map<int, BaseComponent*> m_ComponentMap;
		int m_ComponentsRegistered = 0;
	};
}




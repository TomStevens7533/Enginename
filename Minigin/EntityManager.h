#pragma once
#include <set>

#include "BaseComponent.h"
#include <unordered_map>
#include <unordered_set>
#include <typeinfo>

namespace dae 
{

	class EntityManager 
	{
	public:
		EntityManager() = default;
		~EntityManager();




		template<class TComponent>
		bool AddComponent(std::shared_ptr<BaseComponent>& component)
		{
			if (m_ComponentMap.contains(component)) //return false if map already contains component
				return false;
			m_ComponentMap.insert(component);
			return true;
		}

		template<class TComponent>
		bool RemoveComponent() 
		{
			if (m_ComponentMap.erase(typeid(TComponent).hash_code()) == 0)
				return false;
			else
				return true;
		}

		template<class TComponent>
		std::shared_ptr<TComponent> GetComponent()
		{
			//size_t bucket = typeid(TComponent).hash_code() % m_ComponentMap.bucket_count();
			auto it = std::find_if(m_ComponentMap.begin(), m_ComponentMap.end(), [](std::shared_ptr<BaseComponent> element)
			{
					if (typeid(*element.get()).hash_code() == typeid(TComponent).hash_code())
						return true;
					else
						return false;
			});

			if (it != m_ComponentMap.end())
			{
				return std::dynamic_pointer_cast<TComponent>(*it);
			}
			return nullptr;
		}


		void Update();
		void LateUpdate();
		void Render() const;

	private:
		struct BaseComponentHashCalculator {
		public:
			size_t operator()(const std::shared_ptr<BaseComponent>& str) const {
				auto& ti1 = typeid(str);
				return std::hash<size_t>()(ti1.hash_code());
			}
		};
	private:
		std::unordered_set<std::shared_ptr<BaseComponent>, BaseComponentHashCalculator> m_ComponentMap;
		int m_ComponentsRegistered = 0;
	};
}




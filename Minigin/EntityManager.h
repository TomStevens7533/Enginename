#pragma once
#include <map>

namespace dae {
	class BaseComponent;

	class EntityManager
	{
	public:
		EntityManager() = default;
		~EntityManager();

		bool AddComponent(int id, BaseComponent* component);
		bool RemoveComponent(int id);
		BaseComponent const* GetComponent(int id);


		void Update();
		void LateUpdate();
		void Render() const;
	private:
		std::map<int, BaseComponent*> m_ComponentMap;
		int m_ComponentsRegistered = 0;
	};
}




#include "MiniginPCH.h"
#include "EntityManager.h"
#include "BaseComponent.h"

namespace dae {

	EntityManager::~EntityManager()
	{
		for (auto mapPair : m_ComponentMap)
		{
			delete mapPair.second;
			mapPair.second = nullptr;
		}
	}

	bool EntityManager::AddComponent(int id, BaseComponent* component)
	{
		if (m_ComponentMap.contains(id)) //return false if map already contains component
			return false;
		m_ComponentMap.insert(std::make_pair(id, component));
		return true;
	}
	void EntityManager::Update()
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair.second->Update();
		}
	}

	void EntityManager::LateUpdate()
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair.second->LateUpdate();
		}
	}

	void EntityManager::Render() const
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair.second->Render();
		}
	}

	bool dae::EntityManager::RemoveComponent(int id)
	{
		if (m_ComponentMap.erase(id) == 0)
			return false;
		else
			return true;
	}

	BaseComponent const* dae::EntityManager::GetComponent(int id)
	{
		return m_ComponentMap.at(id);
	}


}

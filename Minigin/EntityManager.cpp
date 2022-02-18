#include "MiniginPCH.h"
#include "EntityManager.h"

namespace dae {

	EntityManager::~EntityManager()
	{
		for (auto mapPair : m_ComponentMap)
		{
			delete mapPair.second;
			mapPair.second = nullptr;
		}
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

}

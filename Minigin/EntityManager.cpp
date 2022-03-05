#include "MiniginPCH.h"
#include "EntityManager.h"

namespace dae {

	EntityManager::~EntityManager()
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair.reset();
		}
	}


	void EntityManager::Update()
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair->Update();
		}
	}

	void EntityManager::LateUpdate()
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair->LateUpdate();
		}
	}

	void EntityManager::Render() const
	{
		for (auto mapPair : m_ComponentMap)
		{
			mapPair->Render();
		}
	}

}

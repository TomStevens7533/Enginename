#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae {


	ComponentContext RenderComponent::m_ComponentContext = ComponentContext{ false,  INT_MAX };


	RenderComponent::RenderComponent()
	{
		//set ID in base class
		if (m_ComponentContext.isRegistered)
			m_RegisteredToID = m_ComponentContext.m_ComponentID;

	



	}

	RenderComponent::~RenderComponent()
	{

	}

	void RenderComponent::Render() const
	{
		//Renderer::GetInstance().RenderTexture(*std::reinterpret_pointer_cast<Texture2D>(m_DataToRender), m_Position.x, m_Position.y);
	}

	void RenderComponent::Update()
	{

	}

	void RenderComponent::LateUpdate()
	{

	}

	void RenderComponent::SetPos(const glm::vec2 pos)
	{
		m_Position = pos;
	}

	void RenderComponent::SetData(std::shared_ptr<void> newData)
	{
		m_DataToRender = newData;
	}


}
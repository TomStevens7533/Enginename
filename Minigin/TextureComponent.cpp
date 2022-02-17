#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <limits.h>
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae {

	ComponentContext TextureComponent::m_ComponentContext = ComponentContext{false,  INT_MAX };

	TextureComponent::TextureComponent()
	{
		//set ID in base class
		if (m_ComponentContext.isRegistered)
			m_RegisteredToID = m_ComponentContext.m_ComponentID;
	}

	TextureComponent::~TextureComponent()
	{
		m_Texture.reset();
	}


	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void TextureComponent::SetPosition(const glm::vec2& pos)
	{
		m_Position = pos;
	}

	void TextureComponent::Render() const
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_Position.x, m_Position.y);
	}

	void TextureComponent::Update()
	{

	}

	void TextureComponent::LateUpdate()
	{

	}

};



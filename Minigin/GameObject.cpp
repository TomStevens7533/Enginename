#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


namespace dae {
	GameObject::~GameObject() = default;

	void GameObject::Update()
	{
		m_EntityManager.Update();

		auto* fpsComponent =  m_EntityManager.GetComponent<FPSComponent>();
		auto* textComponent = m_EntityManager.GetComponent<TextComponent>();

		if (fpsComponent != nullptr && textComponent != nullptr) {
			textComponent->SetText(std::to_string(fpsComponent->GetFpsCount()));
		}

	}

	void GameObject::LateUpdate()
	{
		m_EntityManager.LateUpdate();
	}

	void GameObject::Render() const
	{
		m_EntityManager.Render();
	}
	void GameObject::SetPosition(float x, float y)
	{
		m_Transform.SetPosition(x, y, 0.0f);
	}

}

//void dae::GameObject::SetParent(GameObject* parent)
//{
//}
//
//dae::GameObject* dae::GameObject::GetParent() const
//{
//	return nullptr;
//}
//
//size_t dae::GameObject::GetChildCount() const
//{
//	return size_t();
//}
//
//dae::GameObject* dae::GameObject::GetChildAt(INT Index) const
//{
//	return nullptr;
//}
//
//void dae::GameObject::RemoveChild(int index)
//{
//}
//
//void dae::GameObject::AddChild(GameObject* go)
//{
//}

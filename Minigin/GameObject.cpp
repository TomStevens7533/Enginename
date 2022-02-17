#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	m_EntityManager.Update();
}

void dae::GameObject::LateUpdate()
{
	m_EntityManager.LateUpdate();
}

void dae::GameObject::Render() const
{
	m_EntityManager.Render();
}

void dae::GameObject::AddComponent(BaseComponent* component, int id)
{
	m_EntityManager.AddComponent(id, component);
}

void dae::GameObject::GetComponent(int id)
{
	m_EntityManager.GetComponent(id);
}
void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

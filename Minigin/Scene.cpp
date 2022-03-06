#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Minigin.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;



void Scene::Update()
{
	for(auto& layer : m_LayerStack)
	{
		layer->OnUpdate();

		for (auto& object : layer->GetLayerObjects())
		{
			object->Update();
		}
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& layer : m_LayerStack)
	{
		layer->OnFixedUpdate();
	}
}
void Scene::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}
void Scene::Render() const
{
	for (const Layer* currentLayer : m_LayerStack)
	{

		currentLayer->OnImGuiRender();

		for (auto& object : currentLayer->GetLayerObjects())
		{
			object->Render();
		}

	}



}

void Scene::LateUpdate()
{
	for (auto& layer : m_LayerStack)
	{
		layer->OnLateUpdate();

		for (auto& object : layer->GetLayerObjects())
		{
			object->LateUpdate();
		}
	}
}


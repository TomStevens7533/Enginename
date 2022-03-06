#pragma once
#include "LayerStack.h"
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;

		inline std::string GetSceneName() { return m_Name; }
		void PushLayer(Layer* layer);


		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string m_Name;

		LayerStack m_LayerStack;


		static unsigned int m_IdCounter; 
	};

}

#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "EntityManager.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void LateUpdate() override;
		void Render() const override;

		void AddComponent(BaseComponent* component, int id);
		void GetComponent(int id);
		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_Texture{};
		EntityManager m_EntityManager;
		
	};
}

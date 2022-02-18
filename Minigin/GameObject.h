#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "EntityManager.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void LateUpdate() override;
		void Render() const override;

		template<class TComponent>
		bool AddComponent(BaseComponent* component) {
			return m_EntityManager.AddComponent<TComponent>(component);
		}
		template<class TComponent>
		TComponent* const GetComponent() {
			return m_EntityManager.GetComponent<TComponent>();
		}
		template<class TComponent>
		void RemoveComponent() {
			return m_EntityManager.RemoveComponent<TComponent>();
		}

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//void SetParent(GameObject* parent);
		//GameObject* GetParent() const;
		//size_t GetChildCount() const;
		//GameObject* GetChildAt(INT Index) const;
		//void RemoveChild(int index);
		//void AddChild(GameObject* go);


	private:
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_Texture{};
		EntityManager m_EntityManager;
		
	};
}

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
		void FixedUpdate() override;
		void Render() const override;

		template<class TComponent>
		bool AddComponent(std::shared_ptr<BaseComponent> component) {
			return m_EntityManager.AddComponent<TComponent>(component);
		}
		template<class TComponent>
		std::shared_ptr<TComponent> GetComponent() {
			return m_EntityManager.GetComponent<TComponent>();
		}
		template<class TComponent>
		bool RemoveComponent() {
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

		void SetParent(GameObject* parent);
		GameObject* GetParent() const;
		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(INT Index) const;
		void RemoveChild(int index);
		void AddChild(std::shared_ptr<GameObject>& go);
		void ChangeRootPos(int newRootPos);
		int GetPosFromRoot();


	private:
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?

		//parent child
		GameObject* m_Parent = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		int m_PositionFromRoot = 0;

		//Entities
		EntityManager m_EntityManager;
		
	};
}

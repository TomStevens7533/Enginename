#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae {
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent();
		~TextureComponent();

		inline static const int GetComponentID() { return m_ComponentContext.m_ComponentID; }
		inline static void SetComponentID(int newID) {
			m_ComponentContext.m_ComponentID = newID; 
			m_ComponentContext.isRegistered = true;
		}
		void SetTexture(const std::string& filename);
		void SetPosition(const glm::vec2& pos);

		void Render() const override;
		void Update() override;
		void LateUpdate() override;

	private:
		static ComponentContext m_ComponentContext;
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec2 m_Position;
	};
}



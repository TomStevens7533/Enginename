#pragma once
#include "BaseComponent.h"
#include <memory>
#include "Font.h"
#include <string>
#include "glm/glm.hpp"
#include "Texture2D.h"

namespace dae {
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		~TextComponent();

		inline static const int GetComponentID() { return m_ComponentContext.m_ComponentID; }
		inline static void SetComponentID(int newID) {
			m_ComponentContext.m_ComponentID = newID;
			m_ComponentContext.isRegistered = true;
		}
		void SetText(const std::string& text);
		void SetPosition(const glm::vec2& pos);

		void Render() const override;
		void Update() override;
		void LateUpdate() override;

	private:
		static ComponentContext m_ComponentContext;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

		bool m_NeedsUpdate;
		std::string m_Text;


		glm::vec2 m_Position;
	};
}


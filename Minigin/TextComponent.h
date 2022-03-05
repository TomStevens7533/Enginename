#pragma once
#include "BaseComponent.h"
#include <memory>
#include "Font.h"
#include <string>

#include "glm/glm.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "RenderComponent.h"
#include "OpenGLVertexArray.h"


namespace dae {
	class BaseProgram;//https://learnopengl.com/In-Practice/Text-Rendering
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
		void SetColor(const glm::vec3& color);
		void SetScale(float scale);


		void Render() const override;
		void Update() override;
		void LateUpdate() override;

	private:
		static ComponentContext m_ComponentContext;
		std::shared_ptr<Font> m_Font;

		bool m_NeedsUpdate;
		std::string m_Text;

		std::shared_ptr<BaseProgram> m_RenderProgram;

		std::unique_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Buffer> m_CharBuffer;

		glm::vec3 m_Color = glm::vec3{ 1.f, 1.f, 1.f };
		glm::vec2 m_Pos;
		float m_Scale = 1.f;


		//TODO Get This from cameracontext
		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	};
}



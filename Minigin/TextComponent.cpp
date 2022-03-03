#include "MiniginPCH.h"
#include "TextComponent.h"
#include <glad/glad.h>

#include "ResourceManager.h"

namespace dae {
	ComponentContext TextComponent::m_ComponentContext = ComponentContext{ false,  INT_MAX };

	TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
		: m_NeedsUpdate(true), m_Text(text), m_Font(font)
	{
		//set ID in base class
		if (m_ComponentContext.isRegistered)
			m_RegisteredToID = m_ComponentContext.m_ComponentID;

		m_RenderProgram = ResourceManager::GetInstance().GetProgram(ShaderUseType::TEXT_Shader);

		//create large enough b
		m_VertexArray = std::make_unique<VertexArray>();
		m_CharBuffer = std::make_shared<Buffer<float>> ((float*)(NULL), (uint32_t)(sizeof(float) * 6 * 4), BufferTypes::Dynamic);
		m_VertexArray->Bind();
		m_VertexArray->AddBuffer(m_CharBuffer);

		m_VertexArray->Unbind();

		m_RenderProgram->SetUniformMatrix4(projection, "projection", BaseProgram::ShaderTypes::T_VertexShader);
		m_RenderProgram->Bind();
		Renderer::GetInstance().SetBlendState();
	}

	TextComponent::~TextComponent()
	{
		m_Font.reset();
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}

	void TextComponent::SetPosition(const glm::vec2& pos)
	{
		m_Pos = pos;
	}

	void TextComponent::SetColor(const glm::vec3& color)
	{
		m_Color = color;
	}

	void TextComponent::SetScale(float scale)
	{
		m_Scale = scale;
	}

	void TextComponent::Render() const
	{
		//TODO add texture component for the text;

		glUniform3f(glGetUniformLocation(m_RenderProgram->GetProgramID(), "textColor"), m_Color.x, m_Color.y, m_Color.z);
		glActiveTexture(GL_TEXTURE0);
		m_VertexArray->Bind();

		auto Characters = m_Font->GetCharTexture();
		auto pos = m_Pos;
		// iterate through all characters
		std::string::const_iterator c;
		for (c = m_Text.begin(); c != m_Text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = pos.x + ch.Bearing.x * m_Scale;
			float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * m_Scale;

			float w = ch.Size.x * m_Scale;
			float h = ch.Size.y * m_Scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			m_CharBuffer->Bind();
			m_CharBuffer->RemakeBuffer(0, sizeof(vertices), vertices);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			m_CharBuffer->Unbind();
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			pos.x += (ch.Advance >> 6) * m_Scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
		m_VertexArray->Unbind();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextComponent::Update()
	{
	}

	void TextComponent::LateUpdate()
	{

	}



}

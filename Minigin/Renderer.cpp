#include "MiniginPCH.h"
#include "Renderer.h"
#include <glad/glad.h>
#include "OpenGLVertexArray.h"
#include "Program.h"
#include "SceneManager.h"
#include "Texture2D.h"

namespace dae
{
	void dae::Renderer::SetBlendState()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void dae::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray,
		const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform)
	{
		program->Bind();
		program->SetUniformMatrix4(transform, "projection", BaseProgram::ShaderTypes::T_VertexShader);
		vertexArray->Bind();

		//glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void dae::Renderer::EnableWireFrame()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void dae::Renderer::DisableWireFrame()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}


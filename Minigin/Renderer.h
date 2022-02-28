#pragma once
#include "Singleton.h"

namespace dae
{
	class OpenGLVertexArray;
	class BaseProgram;
	class Texture2D;
	
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void SetBlendState();
		void Submit(const std::shared_ptr<OpenGLVertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform = glm::mat4(1.0f));

		void EnableWireFrame();
		void DisableWireFrame();

		friend class Singleton<Renderer>;

	public:
	
	};
}


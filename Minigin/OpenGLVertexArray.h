#pragma once
#include <memory>
#include <vector>
#include "OpenGLBuffer.h"

namespace dae
{




	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();

		 ~OpenGLVertexArray();

		 void Bind() const ;
		 void Unbind() const ;

		 const std::vector<std::shared_ptr<OpenGLVertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		 const std::shared_ptr<OpenGLIndexBuffer>& GetIndexBuffer() const { return m_IndexBuffers; }


		 void AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer);
		 void AddIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer);

	private:
		std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_VertexBuffers;
		std::shared_ptr<OpenGLIndexBuffer> m_IndexBuffers;
		uint32_t m_RendererID = 1;

	private:
		GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
			default:						return GL_INT;
			}
		}


	};


}

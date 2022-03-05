#pragma once
#include <memory>
#include <vector>
#include "OpenGLBuffer.h"
#include <type_traits>
#include <any>

namespace dae
{

	enum class BufferTypes
	{
		Static, Dynamic
	};
	class Buffer {
	public:
		Buffer(void* data, uint32_t size, BufferTypes type) {
			//Create BufferLayout

				glGenBuffers(1, &m_RendererID);
				glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
				glBufferData(GL_ARRAY_BUFFER, size, data, type == BufferTypes::Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
			
		}
		~Buffer() {
			glDeleteBuffers(1, &m_RendererID);
		}

		void RemakeBuffer(int offset, int size, void* data) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

		}
		void Bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		};
		void Unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		};
		const BufferLayout GetLayout() const { return m_Layout; }
	private:
		uint32_t m_RendererID = UINT32_MAX;
		uint32_t m_Count = 0;
		BufferLayout m_Layout;
	};

	class VertexArray {
	public:
		VertexArray() {
			glGenVertexArrays(1, &m_RendererID);
		}
		~VertexArray() {
			glDeleteVertexArrays(1, &m_RendererID);
		}

		void Bind() const {
			glBindVertexArray(m_RendererID);
		}
		void Unbind() const {
			glBindVertexArray(0);
		}
		const std::vector < std::any >&   GetBuffers()
		{
			return m_Buffers;
		}

		template<class TData>
		void AddBuffer(const std::shared_ptr<Buffer> buffer) {
			uint32_t index = 0;
			glBindVertexArray(m_RendererID);

			for (const auto& element : buffer->GetLayout())
			{

				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					buffer->GetLayout().GetStride(),
					&element.Offset);
				index++;
			}
			if (index == 0) {
				glEnableVertexAttribArray(0);
				int byteSize = sizeof(TData);
				glVertexAttribPointer(0, byteSize, GL_FLOAT, GL_FALSE, byteSize * sizeof(float), 0);
			}

			m_Buffers.push_back(buffer);
			buffer->Bind();

		}
	private:
		std::vector<std::any> m_Buffers;
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

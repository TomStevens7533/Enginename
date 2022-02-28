#pragma once
#include <string>
#include <glm/glm.hpp>

namespace dae {

	class BaseShader {
	public:
		BaseShader(std::string path);
		virtual ~BaseShader() {};

		inline const unsigned int GetShaderID() { return m_ShaderID; }

		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) = 0;

		virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID) = 0;

	protected:
		std::string& GetData() { return m_Data; }

	protected:
		unsigned int m_ShaderID;
	private:
		void ParseFile(std::string& path);
	private:
		std::string m_Path;
		std::string m_Data;
	};

	class OpenGLVertexShader : public BaseShader
	{
	public:
		OpenGLVertexShader(const std::string& path);
		virtual ~OpenGLVertexShader();

		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) override;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) override;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID)override;
		virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, uint32_t renderID)override;

	};

	class OpenGLIndexShader : public BaseShader
	{
	public:
		OpenGLIndexShader(const std::string& path);
		virtual ~OpenGLIndexShader();

		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) override;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) override;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID)override;
		virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, uint32_t renderID)override;

	};
}
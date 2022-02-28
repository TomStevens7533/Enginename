
#include <map>

namespace dae {

	class BaseShader;
	class BaseProgram
	{
	public:
		BaseProgram();
		~BaseProgram();

		enum class ShaderTypes
		{
			T_VertexShader,
			T_PixelShader
		};


		void AttachVertexShader(const std::string& path);
		void AttachPixelShader(const std::string& path);

		void Bind() const;
		void UnBind() const;

		void SetUniformMatrix4(const glm::mat4& mat4, const char* name, ShaderTypes type);
		void SetUniformInt(const int index, const char* name, ShaderTypes type) const;
		void SetUniformVec2(const glm::vec2 index, const char* name, ShaderTypes type) const;
		void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, ShaderTypes type) const;


uint32_t GetProgramID() { return  m_RenderID; }

		void ClearShaders();
		virtual void LinkProgram();

	protected:
		uint32_t m_RenderID;
		std::map<ShaderTypes, std::shared_ptr<BaseShader>> m_ShaderMap;
	};


}

#include <map>

#include "Font.h"
#include "Singleton.h"
#include "Program.h"
#include "Renderer.h"

namespace dae {

	enum class ShaderUseType {
		TEXTURE2D_WORLDSPACE_SHADER,
		CUBETEXTURE_LOCALSPACE_SHADER,
		TEXTURE2D_UILOCALSPACE_SHADER,
		TEXT_Shader
	};


	class ResourceManager : public Singleton<ResourceManager> {
	public:
		void Init(const std::string& path) { m_DefaultPath = path; }
		//funtions
		//std::shared_ptr<VertexArray>& GetModel(const std::string modelPath);
		//std::shared_ptr<BaseTexture>& GetTexture(const std::string texturePath, const TextureTypes type);
		const std::shared_ptr<BaseProgram>& GetProgram(ShaderUseType type);
		const std::shared_ptr<Font> GetFont(const std::string& path, int size);




	private:
		//Variables
		//map used for outside resources
		//std::map<std::string, std::shared_ptr<VertexArray>> m_VertexMap;
		//std::map<std::string, std::shared_ptr<BaseTexture>> m_TextureMap;

		std::map<ShaderUseType, std::shared_ptr<BaseProgram>> m_ProgramMap;
		std::map<std::pair<std::string, int>, std::shared_ptr<Font>> m_FontMap;

		friend class Singleton<ResourceManager>;

	private:
		ResourceManager() = default;
		std::string m_DefaultPath;


	};
}

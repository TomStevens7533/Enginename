#pragma once
#include <map>

namespace dae
{
	//https://learnopengl.com/In-Practice/Text-Rendering
	class Font 
	{
	public:
		FT_Face* GetFont();
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		struct Character {
			unsigned int TextureID;  // ID handle of the glyph texture
			glm::ivec2   Size;       // Size of glyph
			glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
			unsigned int Advance;    // Offset to advance to next glyph
		};
	private:

		FT_Library m_FTlib;
		FT_Face m_FTFace;
		unsigned int m_Size;
		std::map<char, Character> m_CharachterMap;
	};
}

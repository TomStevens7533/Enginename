#include "MiniginPCH.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include "Font.h"
#include "glad/glad.h"

FT_Face* dae::Font::GetFont(){
	return &m_FTFace;
}

dae::Font::Font(const std::string& fullPath, unsigned int size) : m_Size(size)
{

	if (FT_Init_FreeType(&m_FTlib)) //Initializes a new freetype object
	{
		throw std::runtime_error(std::string("ERROR::FREETYPE: Could not init FreeType Library"));
	}

	if (FT_New_Face(m_FTlib, fullPath.c_str(), 0, &m_FTFace))
	{
		throw std::runtime_error(std::string("ERROR::FREETYPE: Failed to load font"));
	}
	FT_Set_Pixel_Sizes(m_FTFace, 0, size); //setting with to zero will dinmically calculate width based on height

    // disable byte-alignment restrictio
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

    for (unsigned char c = 0; c < 128; c++) //Only 128 char of ASCII
    {
        // load character glyph 
        if (FT_Load_Char(m_FTFace, c, FT_LOAD_RENDER))
        {
            throw std::runtime_error(std::string("ERROR::FREETYTPE: Failed to load Glyph"));
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_FTFace->glyph->bitmap.width,
            m_FTFace->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_FTFace->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(m_FTFace->glyph->bitmap.width, m_FTFace->glyph->bitmap.rows),
            glm::ivec2(m_FTFace->glyph->bitmap_left, m_FTFace->glyph->bitmap_top),
            m_FTFace->glyph->advance.x
        };
        m_CharachterMap.insert(std::pair<char, Character>(c, character));
    }

    //OpenGl requires that textures have a 4 byte-allignment
    //We require only one byte per pixel that we store in the red(GL_RED)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//clean up resources
    FT_Done_Face(m_FTFace);
    FT_Done_FreeType(m_FTlib);
}

dae::Font::~Font()
{

	FT_Done_Face(m_FTFace);
	FT_Done_FreeType(m_FTlib);
}

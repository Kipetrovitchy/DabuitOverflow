#include "Font.h"
#include "Assert.h"
#include "Log.h"

namespace Resources
{
    #pragma region Constructors / Destructors
    Font::Font(const Font& f) :
        _characters { f._characters }
    {}

    Font::Font(const std::string& path)
    {
        init(path);
    }
    #pragma endregion

    #pragma region Operators
    Font& Font::operator=(const Font& f)
    {
        _characters = f._characters;

        return *this;
    }
    
    #pragma region Methods
    void Font::init(const std::string& path)
    {
        LOG(INFO, "Font:\tLOADING\t\t" + path);
        //Initialize the Freetype library
        FT_Library ft;
        ASSERT_THROW_MSG(FT_Init_FreeType(&ft) == 0, "Error while initializing FreeType lib");
    
        FT_Face face;
        ASSERT_THROW_MSG(FT_New_Face(ft, path.c_str(), 0, &face) == 0, "Error opening the font file");

        //Set the glyph resolution
        FT_Set_Pixel_Sizes(face, 0, 128);

        //Disable alignement because the 'texture' of the glyphs are only red
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        //Load all the characters.
        initCharacters(250, face);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        LOG(INFO, "Font:\tDONE\t\t" + path);
    }
    #pragma endregion

    #pragma region Private Methods
    void Font::initCharacters(GLuint count,FT_Face& face)
    {
        for (GLuint c { 0 }; c < count; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                LOG(WARNING, "Error loading the glyph");
                continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            //Set the glyph texture
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0, GL_RED, GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            //Set the glyph texture's parameter
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character { (GLuint)texture, 
                                  (GLuint)face->glyph->advance.x,
                                  {(float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows},
                                  {(float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top} };
            _characters.emplace(c, character);
        }
    }
    #pragma endregion
} // namespace Resources

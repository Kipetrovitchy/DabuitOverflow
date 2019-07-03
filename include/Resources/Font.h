#ifndef __FONT_H__
#define __FONT_H__

#include <GL/glew.h>
#include <string>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Vec2.h"
#include "Vec3.h"
#include "Shader.h"
#include "Mat.h"

namespace Resources
{
    struct Character
    {
        GLuint              TextureID;  // ID handle of the glyph texture
        GLuint              Advance;    // Offset to advance to next glyph
        Core::Maths::Vec2   Size;       // Size of glyph
        Core::Maths::Vec2   Bearing;    // Offset from baseline to left/top of glyph
    };

    class Font
    {
        private:
            #pragma region Attributes
            std::map<GLchar, Character> _characters;
            #pragma endregion

            #pragma region Private Methods
            void initCharacters(GLuint count, FT_Face& face);
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Font() = default;
            Font(const Font& f);
            Font(const std::string& path);
            ~Font() = default;
            #pragma endregion

            #pragma region Operators
            Font& operator=(const Font& f);
            #pragma endregion

            #pragma region Methods
            void init(const std::string& path);
            #pragma endregion

            #pragma region Accessors
            std::map<GLchar, Character>& characters() { return _characters; }
            std::map<GLchar, Character> characters() const { return _characters; }
            #pragma endregion
    };
} // namespace Resources
#endif // __FONT_H__
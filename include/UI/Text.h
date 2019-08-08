#ifndef __TEXT_H__
#define __TEXT_H__

#include <string>
#include <GL/glew.h>
#include "BaseUIComponent.h"
#include "Font.h"
#include "Shader.h"
#include "VertexUI.h"
#include "Anchor.h"
#include "Colorable.h"

namespace UI
{

    class Text : public BaseUIComponent, public Colorable
    {
        private:
            #pragma region Attributes
            GLuint              _VAO;
            GLuint              _VBO;
            GLuint              _EBO;

            Anchor              _textAnchor;
            GLfloat             _textScale;
            std::wstring        _text;
            Resources::Font*    _font;
            Resources::Shader*  _shader;

            std::vector<VertexUI>   _characters;
            std::vector<GLuint>     _charactersTex;
            #pragma endregion

            #pragma region Private Methods
            Text& initBuffers()     noexcept;
            Text& resetGLBuffers();
            Text& setEBO()          noexcept;
            bool computeCharacterCoordinates(std::vector<VertexUI>& charactersPos, 
                                             GLfloat xpos, GLfloat ypos,
                                             GLfloat w, GLfloat h)          noexcept;
            
            bool clampGlyph(GLfloat xpos, GLfloat ypos, GLfloat w, GLfloat h,
                            GLfloat& uMin, GLfloat& uMax,
                            GLfloat& vMin, GLfloat& vMax)                   noexcept;

            Vec3 anchoredPosition() noexcept;
            GLfloat stringWidth()   noexcept;
            GLfloat biggestHeight() noexcept;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Text()                                                  noexcept;
            Text(const Text& t)                                     noexcept;
            Text(Resources::Font* font, Resources::Shader* shader)  noexcept;
            ~Text() = default;
            #pragma endregion
    
            #pragma region Operators
            Text& operator=(const Text& t) noexcept;
            #pragma endregion
    
            #pragma region Methods
            BaseUIComponent& render(Mat viewProj) noexcept override;

            //Update the text area with the new stats. 
            //Need to be called after modifications of the text
            Text& update() noexcept;
            #pragma endregion
            
            #pragma region Accessors
            BaseUIComponent& setWidth(GLuint width)     noexcept override;
            BaseUIComponent& setHeight(GLuint height)   noexcept override;

            inline Anchor  textAnchor() const { return _textAnchor; }
            inline Anchor& textAnchor()       { return _textAnchor; }

            inline GLfloat     textScale() const { return _textScale; }
            inline GLfloat&    textScale()       { return _textScale; }
            
            inline std::wstring    text() const { return _text; }
            inline std::wstring&   text()       { return _text; }

            inline Resources::Font* font() const { return _font; }
            inline Resources::Font* font()       { return _font; }

            #pragma endregion
    };
} // namespace UI

#endif // __TEXT_H__
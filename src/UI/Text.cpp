#include "Text.h"
#include "Log.h"
#include "Assert.h"
#include <algorithm>


namespace UI
{
    typedef Core::Maths::Vec2 Vec2;
    #pragma region Constuctors / Destructors
    Text::Text() noexcept :
        BaseUIComponent(),
        Colorable(),
        _textAnchor { EAnchor::BOTLEFT},
        _text { L"Text" },
        _font { nullptr }
    {}

    Text::Text(const Text& t) noexcept :
        BaseUIComponent(t),
        Colorable(t),
        _textAnchor { t._textAnchor },
        _text { t._text },
        _font { t._font }
    {
        initBuffers();
        resetGLBuffers();
    }

    Text::Text(Resources::Font* font, Resources::Shader* shader) noexcept :
        BaseUIComponent(),
        Colorable(),
        _textAnchor { EAnchor::MIDCENTER},
        _textScale { 0.2f },
        _text { L"Text" },
        _font { font },
        _shader { shader }
    {
        initBuffers();
        resetGLBuffers();
    }
    #pragma endregion

    #pragma region Operators
    Text& Text::operator=(const Text& t) noexcept
    {
        BaseUIComponent::operator=(t);
        Colorable::operator=(t);
        _text = t._text;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    BaseUIComponent& Text::render(Mat transformParent) noexcept
    {
        //We don't render the object and its children if it is disabled
        if (!_enabled)
            return *this;

        transformParent = transformParent * _transform.TRS();
        if (!_font)
            return *this;
        
        //Set the value for the shader
        _shader->use();
        _shader->setMatrix4("projection", transformParent.elements);
        setColorShader(_shader);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(_VAO);

        for (GLuint i { 0 }; i < _charactersTex.size(); i ++)
        {
            //Bind the texture of the correct glyph
            glBindTexture(GL_TEXTURE_2D, _charactersTex[i]);
            
            //Draw the glyph
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(i * 6 * sizeof(GLuint)));

        }
        //unbind the texture and the VAO
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        renderChildren(transformParent);

        return *this;
    }

    Text& Text::update() noexcept
    {
        resetGLBuffers();

        return *this;
    }
    #pragma endregion

    #pragma region Private Methods
    Text& Text::initBuffers() noexcept
    {
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);
        
        glBindVertexArray(_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW); 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUI) * 6, nullptr, GL_DYNAMIC_DRAW);
        //Set the vertices position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUI), 0);
        glEnableVertexAttribArray(0);
        //Set the vertices uv
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                              sizeof(VertexUI), (GLvoid*)(sizeof(Vec3)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return *this;
    }

    Text& Text::resetGLBuffers()
    {
        ASSERT_OUT_MSG(_font, "Invalid font, or not initialized");
        //Clear all the vectors of previous string.
        _charactersTex.clear();
        std::vector<VertexUI> charactersPos;

        std::wstring::iterator c;

        //Retrieve the font and the start position of the string
        std::map<GLchar, Resources::Character> characters(_font->characters());
        Resources::Character ch;
        Vec3 charPosition { anchoredPosition() };

        GLfloat xpos, ypos, w, h; 

        //Loop for all the characters in the string
        for (c = _text.begin(); c != _text.end(); ++c)
        {
            ch = characters[*c];

            //Set the correct position for the actual glyph
            xpos = charPosition.x + ch.Bearing.x * _textScale;
            ypos = charPosition.y - (ch.Size.y - ch.Bearing.y) * _textScale;

            w = ch.Size.x * _textScale;
            h = ch.Size.y * _textScale;

            //Set the character in the vector if it can be seen
            if (computeCharacterCoordinates(charactersPos, xpos, ypos, w, h))
                _charactersTex.push_back(ch.TextureID);

            //Update the position for the next glyph
            charPosition.x += (ch.Advance >> 6) * _textScale;
        }

        //Update the VBO for OpenGL
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUI) * charactersPos.size(),
                     charactersPos.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        setEBO();
        
        return *this;
    }

	Text& Text::setEBO() noexcept
	{
		if (_text.length() == 0)
			return *this;

		#ifdef _WIN32
		GLuint* indices = new GLuint[_text.length() * 6];
		#elif defined(__linux__)
        GLuint indices[_text.length() * 6];
		#endif	

        for (GLuint i { 0 };  i < _text.length(); i++)
        {
            indices[0 + i * 6] = 0 + i * 4;
            indices[1 + i * 6] = 1 + i * 4;
            indices[2 + i * 6] = 2 + i * 4;
            indices[3 + i * 6] = 0 + i * 4;
            indices[4 + i * 6] = 2 + i * 4;
            indices[5 + i * 6] = 3 + i * 4;
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
#ifdef _WIN32
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _text.length() * 6 * sizeof(GLuint), indices, GL_DYNAMIC_DRAW);
#elif defined(__linux__)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
#endif
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		#ifdef _WIN32
		delete[] indices;
		#endif

        return *this;
    }

    bool Text::computeCharacterCoordinates(std::vector<VertexUI>& charactersPos,
                                           GLfloat xpos, GLfloat ypos,
                                           GLfloat w, GLfloat h) noexcept
    {
        GLfloat uMin { 0.f }, uMax { 1.f }, vMin { 0.f}, vMax { 1.f };
        //Clamp the glyph if it cut the borders
        if (clampGlyph(xpos, ypos, w, h, uMin, uMax, vMin, vMax))
        {

            xpos += w * uMin;
            w *= uMax;
            w -= w * uMin;

            GLfloat heightMod = (h * (1 - vMax));
            ypos += heightMod;
            h *= (1 - vMin);
            h -= heightMod;
        }
        else
            return false;
        
        //Set all the vertices of the glyph
        charactersPos.emplace_back(Vec3{xpos, ypos + h, 0.f},     Vec2{uMin, vMin});
        charactersPos.emplace_back(Vec3{xpos, ypos, 0.f},         Vec2{uMin, vMax});
        charactersPos.emplace_back(Vec3{xpos + w, ypos, 0.f},     Vec2{uMax, vMax});
        charactersPos.emplace_back(Vec3{xpos + w, ypos + h, 0.f}, Vec2{uMax, vMin});

        return true;
    }

    bool Text::clampGlyph(GLfloat xpos, GLfloat ypos, GLfloat w, GLfloat h,
                           GLfloat& uMin, GLfloat& uMax, GLfloat& vMin, GLfloat& vMax) noexcept
    {
        GLuint anchorValue { _textAnchor.getValue() };

        Vec3 centerPos { Vec3::zero };

        //The string is placed at left or center on x. We must check the clamp with right
        if (anchorValue & (BIT_LEFT | BIT_CENTER))
        {
            if (xpos + w > centerPos.x + _transform.width() / 2.f)
            {
                GLfloat outWidth { xpos + w - (centerPos.x + _transform.width() / 2.f) };
                uMax = 1 - outWidth / w;
                if (uMax < 0.f)
                    return false;
            }
        }
        
        //The string is placed at right or center on x. We must check the clamp with left
        if (anchorValue & (BIT_CENTER | BIT_RIGHT))
        {
            if (xpos < centerPos.x - _transform.width() / 2.f)
            {
                GLfloat outWidth { centerPos.x  - _transform.width() / 2.f - xpos };
                uMin = outWidth / w;
                if (uMin > 1.f)
                    return false;
            }
        }

        //The string is placed at top or center on y. We must check the clamp with bottom
        if (anchorValue & (BIT_TOP | BIT_MID))
        {
            if (ypos < centerPos.y - _transform.height() / 2.f)
            {
                GLfloat outHeight { centerPos.y  - _transform.height() / 2.f - ypos };
                vMax = 1 - outHeight / h;
                if (vMax > 1.f)
                    return false;
            }
        }

        //The string is placed at bottom or center on y. We must check the clamp with top
        if (anchorValue & (BIT_MID | BIT_BOT))
        {
            if (ypos + h > centerPos.y + _transform.height() / 2.f)
            {
                GLfloat outHeight { ypos + h - (centerPos.y  + _transform.height() / 2.f) };
                vMin = outHeight / h;
                if (vMin < 0.f)
                    return false;
            }
        }

        return true;

    }

    Vec3 Text::anchoredPosition() noexcept
    {
        Vec3 position { Vec3::zero };
        GLuint anchorValue { _textAnchor.getValue() };

        //Update the position based on the y placement
        if (anchorValue & BIT_TOP)
            position.y += _transform.height() / 2.f - biggestHeight();
        else if (anchorValue & BIT_CENTER)
            position.y -= biggestHeight() / 2.f;
        else if (anchorValue & BIT_BOT)
            position.y -= _transform.height() / 2.f;

        //Update the position based on the x placement
        if (anchorValue & BIT_LEFT)
            position.x -= _transform.width() / 2.f;
        else if (anchorValue & BIT_CENTER)
            position.x -= stringWidth() / 2.f;
        else if (anchorValue & BIT_RIGHT)
            position.x += _transform.width() / 2.f - stringWidth();

        return position;
    }

    GLfloat Text::stringWidth() noexcept
    {
        GLfloat width { 0.f};
        std::wstring::iterator c;
        std::map<GLchar, Resources::Character> characters = _font->characters();

        Resources::Character ch;

        //Get the width by adding all the glyph width
        for (c = _text.begin(); c != _text.end(); c++)
            width += (characters[*c].Advance >> 6) * _textScale;

        return width;
    }

    GLfloat Text::biggestHeight() noexcept
    {
        GLfloat height { 0.f };

        std::wstring::iterator c;
        std::map<GLchar, Resources::Character> characters = _font->characters();

        //Get the biggest positive height by checking all the glyphs of the string
        for (c = _text.begin(); c != _text.end(); c++)
            height = std::max(height, characters[*c].Bearing.y * _textScale);
            
        return height;
    }
    #pragma endregion

    #pragma region Accessors
    BaseUIComponent& Text::setWidth(GLuint width) noexcept
    {
        _transform.setWidth(width);
        resetGLBuffers();
        updateChildrenTransform();

        return *this;
    }
    
    BaseUIComponent& Text::setHeight(GLuint height) noexcept
    {
        _transform.setHeight(height);
        resetGLBuffers();
        updateChildrenTransform();

        return *this;
    }
    #pragma endregion
} // namespace UI

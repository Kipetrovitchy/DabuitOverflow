#include "Anchor.h"
#include <iostream>

namespace UI
{
    #pragma region Constructors / Destructors
    Anchor::Anchor() :
        _anchor { BIT_MID | BIT_CENTER }
    {}

    Anchor::Anchor(const Anchor& a) :
        _anchor { a._anchor }
    {}

    Anchor::Anchor(const GLuint anchor) :
        _anchor { anchor }
    {}
    
    Anchor::Anchor(const EAnchor anchor) :
        _anchor { static_cast<GLuint>(anchor) }
    {}
    #pragma endregion

    #pragma region Operators
    Anchor& Anchor::operator=(const Anchor& a)
    {
        _anchor = a._anchor;

        return *this;
    }

    Anchor& Anchor::operator=(const EAnchor& a)
    {
        _anchor = static_cast<GLuint>(a);

        return *this;
    }
    #pragma endregion

    #pragma region Accessors
    Anchor& Anchor::setAnchor(GLuint value) 
    { 
        _anchor = value;
        return *this; 
    }

    Anchor& Anchor::setAnchor(EAnchor value)
    { 
        _anchor = static_cast<GLuint>(value);
        return *this;
    }
    #pragma endregion
} // namespace UI

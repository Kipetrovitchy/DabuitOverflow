#include "Colorable.h"

namespace UI
{
    #pragma region Constructors / Destructors
    Colorable::Colorable() noexcept :
        _color { 1.f, 1.f, 1.f, 1.f }
    {}
    Colorable::Colorable(const Vec4& color) noexcept :
        _color { color }
    {}
    Colorable::Colorable(const Colorable& c) noexcept :
        _color { c._color }
    {}
    #pragma endregion

    #pragma region Operators
    Colorable& Colorable::operator=(const Colorable& c) noexcept
    {
        _color = c._color;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    Colorable& Colorable::setColorShader(Resources::Shader* shader) noexcept
    {
        shader->setVec4("color", _color);

        return *this;
    }
    #pragma endregion
} // namespace UI

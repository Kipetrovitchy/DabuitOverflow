#include "VertexUI.h"

namespace UI
{
    #pragma region Constructors / Destructors
    VertexUI::VertexUI(const VertexUI& v) :
        _pos { v._pos },
        _uv { v._uv}
    {}

    VertexUI::VertexUI(const Core::Maths::Vec3& pos, const Core::Maths::Vec2& uv) :
        _pos { pos },
        _uv { uv }
    {}
    #pragma endregion

    #pragma region Operators
    VertexUI& VertexUI::operator=(const VertexUI& v)
    {
        _pos = v._pos;
        _uv = v._uv;

        return *this;
    }
    #pragma endregion
} // namespace UI

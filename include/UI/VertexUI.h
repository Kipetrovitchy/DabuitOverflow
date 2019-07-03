#ifndef __VERTEX_UI_H__
#define __VERTEX_UI_H__

#include "Vec3.h"
#include "Vec2.h"
namespace UI
{
    struct VertexUI
    {
        #pragma region Attributes
        union
        {
            Core::Maths::Vec3 _pos;
            Core::Maths::Vec3 pos;
        };

        union
        {
            Core::Maths::Vec2 _uv;
            Core::Maths::Vec3 uv;
        };
        #pragma endregion
    
        #pragma region Constructors / Destructors
        VertexUI() = default;
        VertexUI(const VertexUI& v);
        VertexUI(const Core::Maths::Vec3& pos, const Core::Maths::Vec2& uv);
        ~VertexUI() = default;
        #pragma endregion
    
        #pragma region Operators
        VertexUI& operator=(const VertexUI& v);
        #pragma endregion
    };
} // namespace UI

#endif // __VERTEX_UI_H__
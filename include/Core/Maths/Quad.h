#ifndef __QUAD_H__
#define __QUAD_H__

#include "Referential.h"
#include "Mat.h"

namespace Core::Maths
{
    #pragma region Typedefs
    typedef Core::Maths::Mat Mat;
    #pragma endregion
    
    struct Quad
    {
        #pragma region Attributes
        union
        {
            Referential _origin;
            Referential origin;
        };
        union
        {
            float _hWidth;
            float hWidth;
        };
        union
        {
            float _hHeight;
            float hHeight;
        };
        #pragma endregion

        #pragma region Constructors
        Quad() = default;
        Quad(const Referential& origin, float hwidth, float hHeight);
        Quad(const Quad& q);
        ~Quad() = default;
        #pragma endregion

        #pragma region Operators
        Quad& operator=(const Quad& q);
        #pragma endregion

        #pragma region Methods
        bool isOver(const Vec2& p) noexcept;
        bool isOver(Vec3 p)        noexcept;
        #pragma endregion
    };
}

#endif//__QUAD_H__
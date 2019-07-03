#include "Segment.h"

namespace Core::Maths
{
    #pragma region Contructors
    Segment::Segment(const Vec3& a, const Vec3& b):
        _a { a },
        _b { b }
    {}

    Segment::Segment(const Segment& s):
        _a { s._a },
        _b { s._b }
    {}
    #pragma endregion

    #pragma region Operators
    Segment& Segment::operator=(const Segment& s)
    {
        _a = s._a;
        _b = s._b;

        return *this;
    }
    #pragma endregion

    #pragma region Fonctions
    float Segment::sqLength() noexcept
    {
        return (_b - _a).squaredLength();
    }

    float Segment::length() noexcept
    {
        return (_b - _a).length();
    }
    #pragma endregion
}

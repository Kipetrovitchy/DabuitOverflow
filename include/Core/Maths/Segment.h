#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct Segment
    {
        #pragma region Attributes
        union
        {
            Vec3 _a;
            Vec3 a;
        }; 
        union
        {
            Vec3 _b;
            Vec3 b;
        };
        #pragma endregion

        #pragma region Contructors
        Segment() = default;
        Segment(const Vec3& a, const Vec3& b);
        Segment(const Segment& s);
        ~Segment() = default;
        #pragma endregion

        #pragma region Operators
        Segment& operator=(const Segment& s);
        #pragma endregion

        #pragma region Functions
        float sqLength() noexcept;
        float length() noexcept;
        #pragma endregion
    };
    
}

#endif//__SEGMENT_H__
#ifndef __CIRCLE_ARC_H__
#define __CIRCLE_ARC_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct CircleArc
    {
        #pragma region Attributes

        union
        {
            Vec3    _center; 
            Vec3    center;
            Vec3    c;
        };

        union
        {
            Vec3    _start;
            Vec3    start;
            Vec3    s;
        };

        union
        {
            Vec3    _normal;
            Vec3    normal;
            Vec3    n;
        };

        union
        {
            float   _angle;
            float   angle;
            float   a;
        };

        #pragma endregion

        #pragma region Constructors
        CircleArc();
        CircleArc(const Vec3& s, const Vec3& e, const Vec3& w);
        CircleArc(const CircleArc& c);
        ~CircleArc() = default;
        #pragma endregion

        #pragma region Operator
        CircleArc&  operator= (const CircleArc& c);
        #pragma endregion

        #pragma region Function
        Vec3    getPosition(float progress) const;
        #pragma endregion
    };
} /* Maths */

#endif//__CIRCLE_ARC_H__

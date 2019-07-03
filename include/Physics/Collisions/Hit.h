#ifndef __HIT_H__
#define __HIT_H__

#include "Vec3.h"

namespace Physics::Collisions
{
    typedef Core::Maths::Vec3 Vec3;

    struct Hit
    {
        #pragma region Attributes
        union
        {
            Vec3 _intersection;
            Vec3 intersection;
        };

        union 
        {
            Vec3 _normal;
            Vec3 normal;
            Vec3 n;
        };

        union
        {
            float _t;
            float t;
        };
        #pragma endregion

        #pragma region Constructors
        Hit() = default;
        Hit(const Vec3& intersection, const Vec3& normal);
        Hit(const Hit& h);
        ~Hit() = default;
        #pragma endregion

        #pragma region Operators
        Hit& operator=(const Hit& h);
        #pragma endregion
    };
} // Core::Maths


#endif
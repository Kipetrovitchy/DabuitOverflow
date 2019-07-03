#ifndef __CAPSULE_H__
#define __CAPSULE_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct Capsule
    {
            #pragma region Attributes
            union
            {
                Vec3 _p;
                Vec3 p;
            };
            union
            {
                Vec3 _q;
                Vec3 q;
            };
            union
            {
                float _radius;
                float radius;
            };
            #pragma endregion
    
            #pragma region Constructors
            Capsule() = default;
            Capsule(const Vec3& p, const Vec3& q, float radius);
            Capsule(const Capsule& c);
            ~Capsule() = default;
            #pragma endregion
    
            #pragma region Operators
            Capsule& operator=(const Capsule& c);
            #pragma endregion
    };
} // Core::Maths

#endif//__CAPSULE_H__
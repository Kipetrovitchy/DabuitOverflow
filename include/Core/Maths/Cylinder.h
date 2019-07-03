#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct Cylinder
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
                float r;
            };
            #pragma endregion
    
            #pragma region Constructors
            Cylinder() = default;
            Cylinder(const Vec3& p, const Vec3& q, float radius);
            Cylinder(const Cylinder& c);
            ~Cylinder() = default;
            #pragma endregion
    
            #pragma region Operators
            Cylinder& operator=(const Cylinder& c);
            #pragma endregion
    };
} // Core::Maths


#endif//__CYLINDER_H__
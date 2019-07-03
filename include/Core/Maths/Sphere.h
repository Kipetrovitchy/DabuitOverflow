#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Vec3.h"

#define SPHERE_BASE_RADIUS 0.5f

namespace Core::Maths
{
    struct Sphere
    {
        #pragma region Attributes
        union
        {
            Vec3 _origin;
            Vec3 origin;
            Vec3 o;
        };
        union
        {
            float _radius;
            float radius;
            float r;
        };
        #pragma endregion

        #pragma region Contructors
        Sphere();
        Sphere(const Vec3& o, float r);
        Sphere(const Sphere& s);
        ~Sphere() = default;
        #pragma endregion

        #pragma region Operators
        Sphere& operator= (const Sphere& s);
        #pragma endregion
    };
} /* Maths */

#endif//__SPHERE_H__

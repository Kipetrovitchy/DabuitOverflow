#ifndef __PLANE_H__
#define __PLANE_H__

#include <iostream>

#include "Mat.h"
#include "Vec3.h"

namespace Core::Maths
{
    typedef unsigned int uint;

    struct Plane
    {
        #pragma region Constructors
        union 
        {
            Vec3  _normal;
            Vec3  normal;
            Vec3  n;
        };
        union
        {
            float _distance;
            float distance;
            float d;
        };
        #pragma endregion

        
        #pragma region Constructors
        Plane();
        Plane(const Vec3& n, float d);
        Plane(const Vec3& a, const Vec3& b, const Vec3& c);
        Plane(const Vec3& point, const Vec3& normal);
        Plane(const Plane& p);
        virtual ~Plane() = default;
        #pragma endregion

        #pragma region Operators
        Plane& operator= (const Plane& p);
        #pragma endregion

        #pragma region Functions
        float   distanceToPoint(const Vec3& point) const;
        Vec3    closestPoint(const Vec3& point) const;
        bool    getSide(const Vec3& point) const;
        bool    sameSide(const Vec3& point1, const Vec3& point2) const;
        #pragma endregion
        
        static  Vec3    planeIntersection(const Plane& p1,
                                          const Plane& p2,
                                          const Plane& p3);
		static	Plane	mediatorPlane(const Vec3& a, const Vec3& b);
    };
    std::ostream& operator<<(std::ostream& os, const Plane& p);
} /* Maths */

#endif//__PLANE_H__

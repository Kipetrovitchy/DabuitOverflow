#ifndef __SPH_COORD_H__
#define __SPH_COORD_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct SphCoord
    {
        #pragma region Attributes
        union
        {
            float _rho;
            float rho;
            float r;
        };
        union
        {
            float _theta;
            float theta;
            float t;
        };
        union
        {
            float _phi;
            float phi;
            float p;
        };
        #pragma endregion

        #pragma region Constructors
        SphCoord(float r = 0, float t = 0, float p = 0);
        SphCoord(const SphCoord& s);
        ~SphCoord() = default;
        #pragma endregion

        #pragma region Operators
        SphCoord& operator= (const SphCoord& s);
        #pragma endregion

        static Vec3     SphericalToCartesian(const SphCoord& sphCoordinates);
        static SphCoord CartesianToSpherical(const Vec3& position);
    };
} /* Maths */

#endif//__SPH_COORD_H__

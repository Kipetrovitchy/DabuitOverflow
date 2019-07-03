#ifndef __CYL_COORD_H__
#define __CYL_COORD_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct CylCoord
    {
        #pragma region Attributes

        union
        {
            float   _rho;
            float   rho;
            float   r;
        };

        union
        {
            float   _theta;
            float   theta;
            float   t;
        };
        
        union
        {
            float   _z;
            float   z;
        };

        #pragma endregion

        #pragma region Constructors
        CylCoord(float r = 0, float t = 0, float z = 0);
        CylCoord(const CylCoord& c);
        ~CylCoord() = default;
        #pragma endregion
        
        #pragma region Operator
        CylCoord& operator= (const CylCoord& c);
        #pragma endregion

        static Vec3     CylindricToCartesian(const CylCoord& cylCoordinates);
        static CylCoord CartesianToCylindric(const Vec3& position);
    };
} /* Maths */

#endif//__CYL_COORD_H__

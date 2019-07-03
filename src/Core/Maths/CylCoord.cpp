#include "CylCoord.h"
#include <cmath>

namespace Core::Maths
{
    #pragma region Constructor
    CylCoord::CylCoord(float r, float t, float z):
        _rho     { r },
        _theta   { t },
        _z       { z }
    {}

    CylCoord::CylCoord(const CylCoord& c):
        _rho     { c._rho },
        _theta   { c._theta },
        _z       { c._z }
    {}
    #pragma endregion

    #pragma region Operator
    CylCoord& CylCoord::operator= (const CylCoord& c)
    {
        _rho    = c._rho;
        _theta  = c._theta;
        _z      = c._z;

        return *this;
    }
    #pragma endregion

    Vec3     CylCoord::CylindricToCartesian(const CylCoord& cylCoordinates)
    {
        return Vec3(
            cylCoordinates._rho * cosf(cylCoordinates._theta),
            cylCoordinates._rho * sinf(cylCoordinates._theta),
            cylCoordinates._z
        );
    }

    CylCoord CylCoord::CartesianToCylindric(const Vec3& p)
    {
        CylCoord outCoord;
        // Rho is the radius of the cylinder
        outCoord._rho = sqrt(p.x*p.x + p.y*p.y);

        // Set the theta depending on the case
        if (p.x > 0.0f)
        {
            if (p.y >= 0.0f)        outCoord._theta = atan(p.y / p.x);
            else                    outCoord._theta = atan(p.y / p.x) + 2.0f * M_PI;
        }
        else if (p.x < 0.0f)        outCoord._theta = atan(p.y / p.x) + M_PI;
        else
        {
            if (p.y > 0.0f)         outCoord._theta = M_PI / 2.0f;
            else if (p.y < 0.0f)    outCoord._theta = (3.0f * M_PI) / 2.0f;
        }

        // z is the height of the cylinder
        outCoord._z = p.z;

        return outCoord;
    }
} /* Maths */

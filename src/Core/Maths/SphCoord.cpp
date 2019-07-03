#include "SphCoord.h"

#include <cmath>

namespace Core::Maths
{
    SphCoord::SphCoord(float rho, float theta, float phi):
        _rho     { rho },
        _theta   { theta },
        _phi     { phi }
    {}

    SphCoord::SphCoord(const SphCoord& s):
        _rho     { s._rho },
        _theta   { s._theta },
        _phi     { s._phi }
    {}

    SphCoord& SphCoord::operator= (const SphCoord& s)
    {
        _rho   = s._rho;
        _theta = s._theta;
        _phi   = s._phi;

        return *this;
    }

    Vec3     SphCoord::SphericalToCartesian(const SphCoord& s)
    {
        float sinPhi = sinf(s._phi);

        return Vec3(
            s._rho * sinPhi * cosf(s._theta),
            s._rho * sinPhi * sinf(s._theta),
            s._rho * cosf(s._phi)
        );
    }

    SphCoord SphCoord::CartesianToSpherical(const Vec3& p)
    {
        SphCoord outCoord;

        // _rho is the radius of the sphere
        outCoord._rho = p.length();

        // _phi is the angle from the z axis
        outCoord._phi = acos(p.z / outCoord._rho);

        // Get _theta depending on the case
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


        return outCoord;
    }
} /* Maths */
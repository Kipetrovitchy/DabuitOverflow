#include "Hit.h"

namespace Physics::Collisions
{
    Hit::Hit(const Vec3& intersection, const Vec3& normal):
        _intersection   { intersection },
        _normal         { normal }
    {}

    Hit::Hit(const Hit& h):
        _intersection   { h._intersection },
        _normal         { h._normal }
    {}

    Hit& Hit::operator=(const Hit& h)
    {
        _intersection   = h._intersection;
        _normal         = h._normal;

        return *this;
    }
}
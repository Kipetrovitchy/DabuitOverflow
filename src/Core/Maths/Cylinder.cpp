#include "Cylinder.h"

namespace Core::Maths
{
    Cylinder::Cylinder(const Vec3& p, const Vec3& q, float radius):
        _p      { p },
        _q      { q },
        _radius { radius }
    {}

    Cylinder::Cylinder(const Cylinder& c):
        _p      { c._p },
        _q      { c._q },
        _radius { c._radius }
    {}

    Cylinder& Cylinder::operator=(const Cylinder& c)
    {
        _p      = c._p;
        _q      = c._q;
        _radius = c._radius;

        return *this;
    }
} // Core::Maths

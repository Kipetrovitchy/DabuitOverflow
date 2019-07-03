#include "Capsule.h"

namespace Core::Maths
{
    
    Capsule::Capsule(const Vec3& p, const Vec3& q, float radius):
        _p      { p },
        _q      { q },
        _radius { radius }
    {}
    
    Capsule::Capsule(const Capsule& c):
        _p      { c._p },
        _q      { c._q },
        _radius { c._radius }
    {}

    Capsule& Capsule::operator=(const Capsule& c)
    {
        _p      = c._p;
        _q      = c._q;
        _radius = c._radius;

        return *this;
    }
} // Core::Maths

#include "Sphere.h"

namespace Core::Maths
{
    #pragma region Contructors
    Sphere::Sphere():
        _origin  { Vec3::zero },
        _radius  { SPHERE_BASE_RADIUS }
    {}

    Sphere::Sphere(const Vec3& o, float r):
        _origin  { o },
        _radius  { r }
    {}

    Sphere::Sphere(const Sphere& s):
        _origin  { s._origin },
        _radius  { s._radius }
    {}
    #pragma endregion

    #pragma region Operators
    Sphere& Sphere::operator= (const Sphere& s)
    {
        _origin = s._origin;
        _radius = s._radius;

        return *this;
    }
    #pragma endregion
} /* Maths */
#include "Plane.h"

#include <cmath>

namespace Core::Maths
{
    #pragma region Construcotrs
    Plane::Plane():
        _normal    { Vec3::up },
        _distance  { 0.0f }
    {}

    Plane::Plane(const Vec3& n, float d):
        _normal    { n.unit() },
        _distance  { d / n.length() }
    {}

    Plane::Plane(const Vec3& a, const Vec3& b, const Vec3& c):
        Plane(a, (b-a).cross(c-a))
    {}

    Plane::Plane(const Vec3& point, const Vec3& n):
        _normal    { n.unit() },
        _distance  { point.dot(_normal) }
    {}

    Plane::Plane(const Plane& p):
        _normal    { p._normal },
        _distance  { p._distance }
    {}
    #pragma endregion

    #pragma region Operators
    Plane& Plane::operator= (const Plane& p)
    {
        _normal    = p._normal;
        _distance  = p._distance;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    float Plane::distanceToPoint(const Vec3& point) const
    {
        return abs(_normal.x * point.x
                + _normal.y * point.y
                + _normal.z * point.z
                - _distance)
            / _normal.length();
    }

    Vec3 Plane::closestPoint(const Vec3& point) const
    {
        if (getSide(point))
            return point - _normal * distanceToPoint(point);
        else
            return point + _normal * distanceToPoint(point);
    }

    bool Plane::getSide(const Vec3& point) const
    {
        return point.dot(_normal) - _distance > 0;
    }

    bool Plane::sameSide(const Vec3& point1, const Vec3& point2) const
    {
        return  (point1.dot(_normal) - _distance > 0) ==
                (point2.dot(_normal) - _distance > 0);
    }
    #pragma endregion

    Vec3 Plane::planeIntersection(const Plane& p1,
                                const Plane& p2,
                                const Plane& p3)
    {
        float* elemA = new float[9]
        {
            p1._normal.x, p1._normal.y, p1._normal.z,
            p2._normal.x, p2._normal.y, p2._normal.z,
            p3._normal.x, p3._normal.y, p3._normal.z
        };
        Mat A(elemA, 3, 3);
        

        Vec3 B(p1._distance, p2._distance, p3._distance);

        return A.inverse() * B;
    }

    Plane Plane::mediatorPlane(const Vec3& a, const Vec3& b)
    {
        return Plane(Vec3::center(a, b), Vec3::vec3FromPoints(a, b));
    }

    std::ostream& operator<<(std::ostream& os, const Plane& p)
    {
        os  << p._normal.x << "x "
            << p._normal.y << "y "
            << p._normal.z << "z "
            << " = " << -p._distance;

        return os;
    }
} /* Maths */

#include "Quad.h"
#include "Transform.h"

namespace Core::Maths
{
    Quad::Quad(const Referential& origin, float hWidth, float hHeight):
        _origin     { origin },
        _hWidth     { hWidth },
        _hHeight    { hHeight }
    {}

    Quad::Quad(const Quad& q):
        _origin     { q._origin },
        _hWidth     { q._hWidth },
        _hHeight    { q._hHeight }
    {}

    Quad& Quad::operator=(const Quad& q)
    {
        _origin     = q._origin;
        _hWidth     = q._hWidth;
        _hHeight    = q._hHeight;

        return *this;
    }

    bool Quad::isOver(const Vec2& p) noexcept
    {
        Vec3 point { p };

        return isOver(point);
    }

    bool Quad::isOver(Vec3 p) noexcept
    {
         // Get the matrix world to local
        std::cout << "world: " << p << std::endl;
        Mat wToLocMat { Physics::Transform::worldToLocal(_origin) };
        // Translate the point into local
        p = wToLocMat * p;
        std::cout << "local: " << p << std::endl;
        std::cout << "_hWidth " << _hWidth << std::endl;
        std::cout << "_hHeight " << _hHeight << std::endl;

        //If the vector is smaller than the half size on all three axes then P is in the AABB
        return (std::abs(p.x) < _hWidth &&
                std::abs(p.z) < _hHeight);
    }
} // Core::Maths

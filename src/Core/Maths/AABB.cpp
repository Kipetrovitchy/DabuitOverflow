#include "AABB.h"
#include "Vec3.h"

#include <algorithm>

namespace Core::Maths
{
    #pragma region Constructors
    AABB::AABB(const Vec3& o, float hW, float hH, float hD):
        _origin  { o },
        _halfW   { hW },
        _halfH   { hH },
        _halfD   { hD }
    {}

    AABB::AABB(const AABB& o):
        _origin  { o._origin },
        _halfW   { o._halfW },
        _halfH   { o._halfH },
        _halfD   { o._halfD }
    {}
    #pragma endregion

    #pragma region Operator
    AABB&   AABB::operator= (const AABB& o)
    {
        _origin = o._origin;
        _halfW  = o._halfW;
        _halfH  = o._halfH;
        _halfD  = o._halfD;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    bool AABB::pointIsIn(Vec3 p) const
    {
        //Calculate the vector PO
        p = _origin - p;

        //If the vector is smaller than the half size on all three axes then P is in the AABB
        return !(std::abs(p.x) > _halfW ||
                 std::abs(p.y) > _halfH ||
                 std::abs(p.z) > _halfD);
    }

    Quad AABB::quadLeft() const
    {
        Referential quadRef(_origin + Vec3::left * halfW, 
            Vec3::up, Vec3::left, Vec3::forward);
        return {quadRef, halfH, halfD};
    }
    
    Quad AABB::quadRight() const
    {
        Referential quadRef(_origin + Vec3::right * halfW, 
            Vec3::down, Vec3::right, Vec3::forward);
        return {quadRef, halfH, halfD};
    }

    Quad AABB::quadBottom() const
    {
        Referential quadRef(_origin + Vec3::down * halfH, 
            Vec3::right, Vec3::down, Vec3::backward);
        return {quadRef, halfW, halfD};
    }

    Quad AABB::quadTop() const
    {
        Referential quadRef(_origin + Vec3::up * halfH, 
            Vec3::right, Vec3::up, Vec3::forward);
        return {quadRef, halfW, halfD};
    }

    Quad AABB::quadBack() const
    {
        Referential quadRef(_origin + Vec3::backward * halfD, 
            Vec3::up, Vec3::backward, Vec3::left);
        return {quadRef, halfH, halfW};
    }

    Quad AABB::quadFront() const
    {
        Referential quadRef(_origin + Vec3::forward * halfD, 
            Vec3::down, Vec3::forward, Vec3::left);
        return {quadRef, halfH, halfW};
    }
    #pragma endregion
} /* Maths */
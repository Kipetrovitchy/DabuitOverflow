#include "OBox.h"
#include "Mat.h"
#include "Transform.h"
#include "Referential.h"
#include "algorithm"
#include "Plane.h"

namespace Core::Maths
{
    #pragma region Constructors
    OBox::OBox(const Referential& r, float hW, float hH, float hD):
        _origin  { r },
        _halfW   { hW },
        _halfH   { hH },
        _halfD   { hD }
    {}

    OBox::OBox(const OBox& o):
        _origin  { o._origin },
        _halfW   { o._halfW },
        _halfH   { o._halfH },
        _halfD   { o._halfD }
    {}
    #pragma endregion

    #pragma region Operator
    OBox&   OBox::operator= (const OBox& o)
    {
        _origin = o._origin;
        _halfW  = o._halfW;
        _halfH  = o._halfH;
        _halfD  = o._halfD;


        return *this;
    }
    #pragma endregion

    #pragma region Functions
    AABB OBox::getAABBFromPoints(Vec3* points) const  
    {
        Mat localToWorld = Physics::Transform::localToWorld(_origin);

        Vec3 max(-std::numeric_limits<float>::max()); 
        Vec3 min( std::numeric_limits<float>::max());

        // Get the
        for (int i = 0; i < 8; ++i)
        {
            max.x = (max.x > points[i].x) ? max.x : points[i].x;
            max.y = (max.y > points[i].y) ? max.y : points[i].y;
            max.z = (max.z > points[i].z) ? max.z : points[i].z;
            min.x = (min.x < points[i].x) ? min.x : points[i].x;
            min.y = (min.y < points[i].y) ? min.y : points[i].y;
            min.z = (min.z < points[i].z) ? min.z : points[i].z;
        }

        return AABB(
            _origin.origin, 
            (max.x - min.x) / 2.0f,
            (max.y - min.y) / 2.0f,
            (max.z - min.z) / 2.0f
        );
    }

    AABB OBox::getLocalAABB() const
    {
        return AABB(
            Vec3::zero, 
            halfW,
            halfH,
            halfD
        );
    }
    
    bool OBox::pointIsIn(Vec3 p) const
    {
        // Get the matrix world to local
        Mat wToLocMat { Physics::Transform::worldToLocal(_origin) };
        // Translate the point into local
        p = wToLocMat * p;

        //If the vector is smaller than the half size on all three axes then P is in the AABB
        return !(std::abs(p.x) > _halfW ||
                 std::abs(p.y) > _halfH ||
                 std::abs(p.z) > _halfD);
    }

    Quad OBox::quadLeft() const
    {
        Referential quadRef(_origin.origin - _origin.i * halfW,
            _origin.j, -_origin.i, _origin.k);
        return {quadRef, halfH, halfD};
    }

    Quad OBox::quadRight() const
    {
        Referential quadRef(_origin.origin + _origin.i * halfW,
            - _origin.j, _origin.i, _origin.k);
        return {quadRef, halfH, halfD};
    }

    Quad OBox::quadBottom() const
    {
        Referential quadRef(_origin.origin - _origin.j * halfH,
            _origin.i, -_origin.j, -_origin.k);
        return {quadRef, halfW, halfD};
    }

    Quad OBox::quadTop() const
    {
        Referential quadRef(_origin.origin + _origin.j * halfH,
            _origin.i, _origin.j, _origin.k);
        return {quadRef, halfW, halfD};
    }

    Quad OBox::quadBack() const
    {
        Referential quadRef(_origin.origin - _origin.k * halfD,
            _origin.j, -_origin.k, -_origin.i);
        return {quadRef, halfH, halfW};
    }

    Quad OBox::quadFront() const
    {
        Referential quadRef(_origin.origin +_origin.k * halfD,
            -_origin.j, _origin.k, -_origin.i);
        return {quadRef, halfH, halfW};
    }


    Vec3* OBox::getAllPoints() const
    {
        // F : front;  B : back;  T : top;  D : down;  R : right;  L : left
        return new Vec3[8]
        {
            _origin.o - _origin.i * _halfW + _origin.j * _halfH + _origin.k * _halfD, // F T L
            _origin.o - _origin.i * _halfW - _origin.j * _halfH + _origin.k * _halfD, // F D L
            _origin.o + _origin.i * _halfW - _origin.j * _halfH + _origin.k * _halfD, // F D R
            _origin.o + _origin.i * _halfW + _origin.j * _halfH + _origin.k * _halfD, // F T R
            _origin.o + _origin.i * _halfW + _origin.j * _halfH - _origin.k * _halfD, // B T R
            _origin.o + _origin.i * _halfW - _origin.j * _halfH - _origin.k * _halfD, // B D R
            _origin.o - _origin.i * _halfW - _origin.j * _halfH - _origin.k * _halfD, // B D L
            _origin.o - _origin.i * _halfW + _origin.j * _halfH - _origin.k * _halfD  // B T L
        };
    }

    Plane OBox::planeLeft() const
    {
        return {_origin.origin - _origin.i * halfW, -_origin.i};
    }

    Plane OBox::planeRight() const
    {
        return {_origin.origin + _origin.i * halfW, _origin.i};
    }

    Plane OBox::planeBottom() const
    {
        return {_origin.origin - _origin.j * halfH, -_origin.j};
    }

    Plane OBox::planeTop() const
    {
        return {_origin.origin + _origin.j * halfH, _origin.j};
    }

    Plane OBox::planeBack() const
    {
        return {_origin.origin - _origin.k * halfD, -_origin.k};
    }

    Plane OBox::planeFront() const
    {
        return {_origin.origin + _origin.k * halfD, _origin.k};
    }
    #pragma endregion
} /* Maths */

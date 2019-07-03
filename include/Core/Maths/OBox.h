#ifndef __OBOX_H__
#define __OBOX_H__

#include "Referential.h"
#include "Quad.h"
#include "AABB.h"
#include "Range.h"
#include "Plane.h"

namespace Core::Maths
{
    struct OBox
    {
        #pragma region Attributes
        union
        {
            Referential     _origin;
            Referential     origin;
            Referential     o;
        };

        union
        {
            float           _halfW;
            float           halfW;
        };

        union
        {
            float           _halfH;
            float           halfH;
        };

        union
        {
            float           _halfD;
            float           halfD;
        };
        #pragma endregion

        #pragma region Constructors
        OBox() = default;
        OBox(const Referential& r, float hW, float hH, float hD);
        OBox(const OBox& o);
        ~OBox() = default;
        #pragma endregion

        #pragma region Operator
        OBox&   operator= (const OBox& o);
        #pragma endregion

        #pragma region Functions
        Vec3* getAllPoints() const;
        AABB getAABBFromPoints(Vec3* points) const;   
        AABB getLocalAABB() const;
        bool pointIsIn(Vec3 p) const;

        Quad quadLeft() const;
        Quad quadRight() const;
        Quad quadBottom() const;
        Quad quadTop() const;
        Quad quadBack() const;
        Quad quadFront() const;

        Plane planeLeft() const;
        Plane planeRight() const;
        Plane planeBottom() const;
        Plane planeTop() const;
        Plane planeBack() const;
        Plane planeFront() const;
        #pragma endregion
    };
} /* Maths */

#endif//__OBOX_H__

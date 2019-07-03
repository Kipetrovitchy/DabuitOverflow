#ifndef __AABB_H__
#define __AABB_H__

#include "Vec3.h"
#include "Quad.h"

namespace Core::Maths
{
    struct AABB
    {
        #pragma region Attributes
        union 
        {
            Vec3    _origin;
            Vec3    origin;
            Vec3    o;
        };
        
        union 
        {
            float   _halfW;
            float   halfW;
        };
        
        union 
        {
            float   _halfH;
            float   halfH;
        };
        
        union 
        {
            float   _halfD;
            float   halfD;
        };
        #pragma endregion

        #pragma region Constructors
        AABB() = default;
        AABB(const Vec3& o, float hW, float hH, float hD);
        AABB(const AABB& o);
        ~AABB() = default;
        #pragma endregion

        #pragma region Operator
        AABB&   operator= (const AABB& o);
        #pragma endregion

        #pragma region Functions
        bool pointIsIn(Vec3 p) const;
        Quad quadLeft() const;
        Quad quadRight() const; 
        Quad quadBottom() const;
        Quad quadTop() const;
        Quad quadBack() const;
        Quad quadFront() const;
        #pragma endregion
    };
} /* Maths */

#endif//__OBOX_H__
#ifndef __SEGMENT_HIT_H__
#define __SEGMENT_HIT_H__

#include "Hit.h"

namespace Physics::Collisions
{
    struct SegmentHit : public Hit
    {
            #pragma region Attributes
            union
            {
                float _t;
                float t;
            };
            #pragma endregion
    
            #pragma region Constructors
            SegmentHit() = default;
            SegmentHit(const SegmentHit& sh);
            ~SegmentHit() = default;
            #pragma endregion
    
            #pragma region Operators
            SegmentHit& operator=(const SegmentHit& sh);
            #pragma endregion
    };
}

#endif//__SEGMENT_HIT_H__
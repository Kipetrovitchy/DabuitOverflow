#include "SegmentHit.h"

namespace Physics::Collisions
{
    SegmentHit::SegmentHit(const SegmentHit& sh):
        Hit (sh),
        _t  { sh._t }
    {}

    SegmentHit& SegmentHit::operator=(const SegmentHit& sh)
    {
        Hit::operator=(sh);
        _t = sh._t;

        return *this;
    }
}
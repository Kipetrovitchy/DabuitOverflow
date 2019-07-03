#include "Range.h"

#include <limits>
#include <iostream>

namespace Core::Maths
{
    Range::Range():
        _min {  std::numeric_limits<float>::max() },
        _max { -std::numeric_limits<float>::max() }
    {}
    
    Range::Range(float min, float max):
        _min { min },
        _max { max }
    {}

    Range::Range(const Range& r):
        _min { r._min },
        _max { r._max }
    {}

    Range& Range::operator=(const Range& r)
    {
        _min = r._min;
        _max = r._max;

        return *this;
    }

    Range& Range::update(float value)
    {
        _min = (_min < value) ? _min : value;
	    _max = (_max > value) ? _max : value;        

        return *this;
    }

    bool Range::isOverlapping(const Range& r) const
    {
        return !(_min > r._max || r._min > _max);
    }
} // Core::Maths

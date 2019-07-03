#ifndef __FIELD_OF_VIEW_H__
#define __FIELD_OF_VIEW_H__

#include "Vec3.h"

namespace Core::Maths
{
    class FieldOfView
    {
    public:
        FieldOfView() = default;
        virtual ~FieldOfView() = default;
        virtual bool canSee(const Vec3& point) const = 0;
    };
} /* Maths */
#endif

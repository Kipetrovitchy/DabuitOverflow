#ifndef __REFERENTIAL_H__
#define __REFERENTIAL_H__

#include "Vec3.h"

namespace Core::Maths
{
    struct Referential
    {
        #pragma region Attributes
        union
        {
            Vec3 _origin;
            Vec3 origin;
            Vec3 o;
        };
        union
        {
            Vec3 _i;
            Vec3 i;
        };
        union
        {
            Vec3 _j;
            Vec3 j;
        };
        union
        {
            Vec3 _k;
            Vec3 k;
        };
        #pragma endregion

        #pragma region Constructors
        Referential() = default;
        Referential(const Vec3& o, const Vec3& i, const Vec3& j, const Vec3& k);
        Referential(const Referential& r);
        ~Referential() = default;
        #pragma endregion

        #pragma region Operators
        Referential&    operator= (const Referential& r);
        #pragma endregion

        #pragma region Functions
        static Referential baseReferential();
        #pragma endregion
    };
} /* Maths */

#endif//__REFERENTIAL_H__
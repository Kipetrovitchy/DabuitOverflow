#include "Referential.h"

namespace Core::Maths
{
    #pragma region Constructors
    Referential::Referential(
        const Vec3& origin,
        const Vec3& i,
        const Vec3& j,
        const Vec3& k):
        _origin  { origin },
        _i       { i.unit() },
        _j       { j.unit() },
        _k       { k.unit() }
    {}

    Referential::Referential(const Referential& r):
        _origin  { r._origin },
        _i       { r._i },
        _j       { r._j },
        _k       { r._k }
    {}
    #pragma endregion

    #pragma region Operators
    Referential&    Referential::operator= (const Referential& r)
    {
        _origin = r._origin;
        _i      = r._i;
        _j      = r._j;
        _k      = r._k;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    Referential baseReferential()
    {
        return Referential(Vec3::zero, Vec3::right, Vec3::up, Vec3::forward);
    }
    #pragma endregion
} /* Maths */
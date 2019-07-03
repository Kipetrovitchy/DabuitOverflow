#include "Triplet.h"

namespace Core::DataStructure
{
    #pragma region Constructors
    Triplet::Triplet(uint v, uint uv, uint n):
        _indiceP  {v},
        _indiceUV {uv},
        _indiceN  {n}
    {}

    Triplet::Triplet(const Triplet& t):
        _indiceP  {t._indiceP},
        _indiceUV {t._indiceUV},
        _indiceN  {t._indiceN}
    {}

    Triplet::~Triplet()
    {}
    #pragma endregion

    #pragma region Operators
    Triplet& Triplet::operator=(const Triplet& t)
    {
        _indiceP  = t._indiceP;
        _indiceUV = t._indiceUV;
        _indiceN  = t._indiceN;

        return *this;
    }

    bool Triplet::operator<(const Triplet& t) const
    {
        if (_indiceP < t._indiceP)
            return true;
        else if (_indiceP == t._indiceP)
        {
            if (_indiceUV < t._indiceUV)
                return true;
            else if (_indiceUV == t._indiceUV)
            {
                if (_indiceN < t._indiceN)
                    return true;
            }

        }

        return false;
    }
    #pragma endregion
} /* Core::Maths */

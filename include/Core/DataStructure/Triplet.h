#ifndef __TRIPLET_H__
#define __TRIPLET_H__

namespace Core::DataStructure
{
    typedef unsigned int uint;
    struct Triplet
    {
        #pragma region Attributes
        union
        {
            uint _indiceP;
            uint indiceP;
            uint p;
        };
        union
        {
            uint _indiceUV;
            uint indiceUV;
            uint uv;
        };
        union
        {
            uint _indiceN;
            uint indiceN;
            uint n;
        };
        #pragma endregion

        #pragma region Contructors
        Triplet(uint v = 0, uint uv = 0, uint n = 0);
        Triplet(const Triplet& t);
        ~Triplet();
        #pragma endregion

        #pragma region Operators
        Triplet&   operator= (const Triplet& t);
        bool       operator< (const Triplet& t) const;
        #pragma endregion
    };
} /* Core::Maths */

#endif//__TRIPLETS_H__

#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "LibMaths.h"

namespace Resources
{
    typedef Core::Maths::Vec4 Vec4;
    typedef Core::Maths::Vec3 Vec3;

    struct Vertex
    {
        #pragma region Attributes
        union
        {
            Vec4 _position;
            Vec4 position;
            Vec4 pos;
        };
        union
        {
            Vec3 _uv;
            Vec3 uv;
        };
        union
        {
            Vec3 _normal;
            Vec3 normal;
            Vec3 n;
        };
        #pragma endregion

        #pragma region Constructors
        Vertex() = default;
        Vertex(const Vec4& position, const Vec3& uv, const Vec3& normal);
        Vertex(const Vertex& v);
        ~Vertex() = default;
        #pragma endregion

        #pragma region Operators
        Vertex& operator=(const Vertex& v);
        #pragma endregion
    };
} /* Resources */

#endif//__VERTEX_H__

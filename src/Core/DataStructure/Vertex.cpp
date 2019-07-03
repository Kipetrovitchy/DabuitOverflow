#include "Vertex.h"

namespace Resources
{
    #pragma region Constructors
    Vertex::Vertex(const Vec4& position, const Vec3& uv, const Vec3& normal):
        _position {position},
        _uv       {uv},
        _normal   {normal}
    {}

    Vertex::Vertex(const Vertex& v):
        _position {v._position},
        _uv       {v._uv},
        _normal   {v._normal}
    {}
    #pragma endregion

    #pragma region Operators
    Vertex& Vertex::operator=(const Vertex& v)
    {
        _position = v._position;
        _uv       = v._uv;
        _normal   = v._normal;

        return *this;
    }
    #pragma endregion
} /* Resources */

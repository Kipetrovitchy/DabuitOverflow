#include "Vec4.h"
#include "Vec3.h"
#include "Vec2.h"
#include <cmath>
#include <string>

namespace Core::Maths
{
    #pragma region Constructors
    Vec4::Vec4(float x, float y, float z, float w):
        _x {x},
        _y {y},
        _z {z},
        _w {w}
    {}

    Vec4::Vec4(const Vec2& vec2, float z, float w):
        _x {vec2._x},
        _y {vec2._y},
        _z {z},
        _w {w}
    {}

    Vec4::Vec4(const Vec3& vec3, float w):
        _x {vec3._x},
        _y {vec3._y},
        _z {vec3._z},
        _w {w}
    {}

    Vec4::Vec4(const Vec4& vec4):
        _x {vec4._x},
        _y {vec4._y},
        _z {vec4._z},
        _w {vec4._w}
    {}
    #pragma endregion

    #pragma region Operators
    Vec4& Vec4::operator=(const Vec4& vec4)
    {
        _x = vec4._x;
        _y = vec4._y;
        _z = vec4._z;
        _w = vec4._w;

        return *this;
    }

    Vec4& Vec4::operator=(const Vec3& vec3)
    {
        _x = vec3._x;
        _y = vec3._y;
        _z = vec3._z;
        _w = 1.0f;

        return *this;
    }

    Vec4 Vec4::operator+(const Vec4& vec4) const
    {
        Vec4 out;

        out._x = _x + vec4._x;
        out._y = _y + vec4._y;
        out._z = _z + vec4._z;
        out._w = _w + vec4._w;

        return out;
    }

    Vec4& Vec4::operator+=(const Vec4& vec4)
    {
        _x += vec4._x;
        _y += vec4._y;
        _z += vec4._z;
        _w += vec4._w;

        return *this;
    }

    Vec4 Vec4::operator-(const Vec4& vec4) const
    {
        Vec4 out;

        out._x = _x - vec4._x;
        out._y = _y - vec4._y;
        out._z = _z - vec4._z;
        out._w = _w - vec4._w;

        return out;
    }

    Vec4& Vec4::operator-=(const Vec4& vec4)
    {
        _x -= vec4._x;
        _y -= vec4._y;
        _z -= vec4._z;
        _w -= vec4._w;

        return *this;
    }

    Vec4 Vec4::operator-() const
    {
        return Vec4(
            -_x,
            -_y,
            -_z,
            -_w
        );
    }

    Vec4 Vec4::operator*(float scale) const
    {
        Vec4 out;

        out._x = _x * scale;
        out._y = _y * scale;
        out._z = _z * scale;
        out._w = _w * scale;

        return out;
    }

    Vec4& Vec4::operator*=(float scale)
    {
        _x *= scale;
        _y *= scale;
        _z *= scale;
        _w *= scale;

        return *this;
    }

    Vec4 Vec4::operator/(float scale) const
    {
        Vec4 out;

        out._x = _x / scale;
        out._y = _y / scale;
        out._z = _z / scale;
        out._w = _w / scale;

        return out;
    }

    Vec4& Vec4::operator/=(float scale)
    {
        _x /= scale;
        _y /= scale;
        _z /= scale;
        _w /= scale;

        return *this;
    }

    float& Vec4::operator[](uint i)
    {
        switch (i)
        {
            case 0:  return _x; break;
            case 1:  return _y; break;
            case 2:  return _z; break;
            default: return _w; break;
        }
    }
    #pragma endregion

    #pragma region Functions
    void Vec4::homogenize()
    {
        if (_w == 0)
            return;

        _x /= _w;
        _y /= _w;
        _z /= _w;
        _w  = 1.0f;
    }

    float Vec4::length() const
    {
        return sqrt(_x*_x + _y*_y + _z*_z + _w*_w);
    }

    float Vec4::squaredLength() const
    {
        return _x*_x + _y*_y + _z*_z + _w*_w;
    }

    void Vec4::unit()
    {
        float len = length();
        if (len == 0)
            return;

        _x /= len;
        _y /= len;
        _z /= len;
        _w /= len;
    }

    Vec4 Vec4::unit() const
    {
        Vec4 out;

        float len = length();
        if (len == 0)
            return out;

        out._x = _x / len;
        out._y = _y / len;
        out._z = _z / len;
        out._w = _w / len;

        return out;
    }

    float Vec4::dot(const Vec4& vec) const
    {
        return _x * vec._x + _y * vec._y + _z * vec._z + _w * vec._w;
    }

    std::string Vec4::to_string() const
    {
        return 
              std::to_string(_x) + "," 
            + std::to_string(_y) + "," 
            + std::to_string(_z) + "," 
            + std::to_string(_w);
    }

    std::ostream& operator<<(std::ostream& os, const Vec4& vec)
    {
        os << vec._x << ",\t" << vec._y << ",\t" << vec._z << ",\t" << vec._w;

        return os;
    }
    #pragma endregion
} /* Maths */
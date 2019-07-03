#include "Vec3.h"
#include "Vec2.h"
#include "Vec4.h"
#include <cmath>
#include <string>

namespace Core::Maths
{    
    Vec3 Vec3::zero     = Vec3( 0.0f,  0.0f,  0.0f);
    Vec3 Vec3::one      = Vec3( 1.0f,  1.0f,  1.0f);
    Vec3 Vec3::up       = Vec3( 0.0f,  1.0f,  0.0f);
    Vec3 Vec3::down     = Vec3( 0.0f, -1.0f,  0.0f);
    Vec3 Vec3::right    = Vec3( 1.0f,  0.0f,  0.0f);
    Vec3 Vec3::left     = Vec3(-1.0f,  0.0f,  0.0f); 
    Vec3 Vec3::forward  = Vec3( 0.0f,  0.0f,  1.0f);
    Vec3 Vec3::backward = Vec3( 0.0f,  0.0f, -1.0f);
    Vec3 Vec3::infinity = Vec3(std::numeric_limits<float>::infinity());

    #pragma region Contructors
    Vec3::Vec3(float value):
        _x {value},
        _y {value},
        _z {value}
    {}

    Vec3::Vec3(float x, float y, float z):
        _x {x},
        _y {y},
        _z {z}
    {}

    Vec3::Vec3(const Vec3& a, const Vec3& b):
        _x {b._x - a._x},
        _y {b._y - a._y},
        _z {b._z - a._z}
    {}

    Vec3::Vec3(const Vec2& vec2, float z):
        _x {vec2.x},
        _y {vec2.y},
        _z {z}
    {}

    Vec3::Vec3(const Vec3& vec3):
        _x  {vec3._x},
        _y  {vec3._y},
        _z  {vec3._z}
    {}

    Vec3::Vec3(const Vec4& vec4):
        _x  {vec4.x},
        _y  {vec4.y},
        _z  {vec4.z}
    {}
    #pragma endregion

    #pragma region Operators
    Vec3& Vec3::operator=(const Vec3& vec3)
    {
        _x = vec3._x;
        _y = vec3._y;
        _z = vec3._z;

        return *this;
    }

    Vec3& Vec3::operator=(const Vec4& vec4)
    {
        _x = vec4.x;
        _y = vec4.y;
        _z = vec4.z;

        return *this;
    }

    Vec3 Vec3::operator+(const Vec3& vec3) const
    {
        Vec3 out   (_x + vec3._x,
                    _y + vec3._y,
                    _z + vec3._z);

        return out;
    }

    Vec3& Vec3::operator+=(const Vec3& vec3)
    {
        _x += vec3._x;
        _y += vec3._y;
        _z += vec3._z;

        return *this;
    }

    Vec3 Vec3::operator-(const Vec3& vec3) const
    {
        Vec3 out   (_x - vec3._x,
                    _y - vec3._y,
                    _z - vec3._z);

        return out;
    }

    Vec3& Vec3::operator-=(const Vec3& vec3)
    {
        _x -= vec3._x;
        _y -= vec3._y;
        _z -= vec3._z;

        return *this;
    }

    Vec3 Vec3::operator-() const
    {
        Vec3 out(-_x, -_y, -_z);

        return out;
    }

    Vec3 Vec3::operator*(float scale) const
    {
        Vec3 vecScale;

        vecScale._x = _x * scale;
        vecScale._y = _y * scale;
        vecScale._z = _z * scale;

        return vecScale;
    }

    Vec3& Vec3::operator*=(float scale)
    {
        _x *= scale;
        _y *= scale;
        _z *= scale;

        return *this;
    }

    Vec3 Vec3::operator*(const Vec3& vec) const
    {
        Vec3 newVec;

        newVec._x = _x * vec._x;
        newVec._y = _y * vec._y;
        newVec._z = _z * vec._z;

        return newVec;
    }

    Vec3& Vec3::operator*=(const Vec3& vec3)
    {
        _x *= vec3._x;
        _y *= vec3._y;
        _z *= vec3._z;

        return *this;
    }

    Vec3 Vec3::operator/(const Vec3& vec) const
    {
        Vec3 newVec;

        newVec._x = _x / vec._x;
        newVec._y = _y / vec._y;
        newVec._z = _z / vec._z;

        return newVec;
    }

    Vec3& Vec3::operator/=(const Vec3& vec3)
    {
        _x /= vec3._x;
        _y /= vec3._y;
        _z /= vec3._z;

        return *this;
    }

    float& Vec3::operator[](uint i)
    {
        switch (i)
        {
            case 0:  return _x; break;
            case 1:  return _y; break;
            default: return _z; break;
        }
    }

    bool Vec3::operator==(const Vec3& vec) const
    {
        return _x == vec._x && _y == vec._y && _z == vec._z; 
    }

    bool Vec3::operator!=(const Vec3& vec) const
    {
        return _x != vec._x || _y != vec._y || _z != vec._z; 
    }
    #pragma endregion

    #pragma region Functions
    float Vec3::length() const
    {
        return sqrt(_x*_x + _y*_y + _z*_z);
    }

    float Vec3::squaredLength() const
    {
        return _x*_x + _y*_y + _z*_z;
    }

    Vec3& Vec3::unit()
    {
        float len = length();
        if (len == 0)
            return *this;

        _x = _x / len;
        _y = _y / len;
        _z = _z / len;

        return *this;
    }

    Vec3 Vec3::unit() const
    {
        Vec3 unit;

        float len = length();
        if (len == 0)
            return unit;

        unit._x = _x / len;
        unit._y = _y / len;
        unit._z = _z / len;

        return unit;
    }

    float Vec3::angle(const Vec3& vec) const
    {
        float len = squaredLength() * vec.squaredLength();
        if (len == 0.0f)
            return 0.0f;

        float div = dot(vec) / sqrt(len);

        if (div > 1.0f)
            return 0.0f;
        else if (div < -1.0f)
            return M_PI;
        
        return acosf(div);
    }

    float Vec3::dot(const Vec3& vec) const
    {
        return _x * vec._x + _y * vec._y + _z * vec._z;
    }

    Vec3 Vec3::cross(const Vec3& vec) const
    {
        Vec3 out;

        out._x = (_y * vec._z) - (_z * vec._y);
        out._y = (_z * vec._x) - (_x * vec._z);
        out._z = (_x * vec._y) - (_y * vec._x);

        return out;
    }

    bool Vec3::equals(const Vec3& vec, float epsilon) const
    {
        return fabs(_x - vec._x) < epsilon &&
                fabs(_y - vec._y) < epsilon &&
                fabs(_z - vec._z) < epsilon;
    }

    void Vec3::round()
    {
        _x = roundf(_x);
        _y = roundf(_y);
        _z = roundf(_z);
    }

    Vec3 Vec3::round() const
    {
        Vec3 vec;

        vec._x = roundf(_x);
        vec._y = roundf(_y);
        vec._z = roundf(_z);

        return vec;
    }
    #pragma endregion

    Vec3 Vec3::center(const Vec3& a, const Vec3& b)
    {
        return (a + b) * (1 / 2.f);
    }


    Vec3 Vec3::vec3FromPoints(const Vec3& v1, const Vec3& v2)
    {
        return Vec3(
            v2._x - v1._x,
            v2._y - v1._y,
            v2._z - v1._z
        );
    }

    float Vec3::angle(const Vec3& v1, const Vec3& v2)
    {
        float len = v1.squaredLength() * v2.squaredLength();
        if (len == 0)
            return 0.f;

        return acos(
            v1.dot(v2) / sqrt(len)
        );
    }

    std::string Vec3::to_string() const
    {
        return std::to_string(_x) + "," + std::to_string(_y) + "," + std::to_string(_z);
    }

    std::ostream& operator<<(std::ostream& os, const Vec3& vec)
    {
        os << vec._x << ",\t" << vec._y << ",\t" << vec._z;

        return os;
    }
} /* Maths */
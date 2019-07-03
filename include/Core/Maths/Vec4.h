#ifndef __VEC4_H__
#define __VEC4_H__

#include <iostream>
#include <string>

namespace Core::Maths
{
    typedef unsigned int uint;

    struct Vec2;
    struct Vec3;
    
    struct Vec4
    {
        #pragma region Attributes
        union
        {
            float _x;
            float x;
            float r;
        };
        union
        {
            float _y;
            float y;
            float g;
        };
        union
        {
            float _z;
            float z;
            float b;
        };
        union
        {
            float _w;
            float w;
            float a;
        };
        #pragma endregion

        #pragma region Constructors
        Vec4() = default;
        Vec4(float x, float y, float z, float w = 0.0f);
        Vec4(const Vec2& vec2, float z = 0.0f, float w = 1.0f);
        Vec4(const Vec3& vec3, float w = 1.0f);
        Vec4(const Vec4& vec4);
        ~Vec4() = default;
        #pragma endregion

        #pragma region Operators
        Vec4&  operator= (const Vec4& vec4);
        Vec4&  operator= (const Vec3& vec3);
        Vec4   operator+ (const Vec4& vec4) const;
        Vec4&  operator+=(const Vec4& vec4);
        Vec4   operator- (const Vec4& vec4) const;
        Vec4&  operator-=(const Vec4& vec4);
        Vec4   operator- () const;
        Vec4   operator* (float scale) const;
        Vec4&  operator*=(float scale);
        Vec4   operator/ (float scale) const;
        Vec4&  operator/=(float scale);
        float& operator[](uint i);
        #pragma endregion

        #pragma region Functions
        float length() const;
        float squaredLength() const;
        void  unit();
        Vec4  unit() const;
        void  homogenize();

        float dot(const Vec4& vec4) const;

        std::string to_string() const;
        #pragma endregion
    };
    std::ostream& operator<<(std::ostream& os, const Vec4& vec);
}

#endif //__VEC4_H__

#ifndef __VEC3_H__
#define __VEC3_H__

#include <iostream>

namespace Core::Maths
{
    typedef unsigned int uint;

    struct Vec2;
    struct Vec4;
    struct Vec3
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
        #pragma endregion

        #pragma region Contructors
        Vec3() = default;
        Vec3(float value);
        Vec3(float x, float y, float z);
        Vec3(const Vec3& a, const Vec3& b);
        Vec3(const Vec2& vec2, float z = 0.0f);
        Vec3(const Vec3& vec3);
        Vec3(const Vec4& vec4);
        ~Vec3() = default;
        #pragma endregion

        #pragma region Operators
        Vec3&  operator= (const Vec3& vec3);
        Vec3&  operator= (const Vec4& vec4);
        Vec3   operator+ (const Vec3& vec3) const;
        Vec3&  operator+=(const Vec3& vec3);
        Vec3   operator- (const Vec3& vec3) const;
        Vec3&  operator-=(const Vec3& vec3);
        Vec3   operator- () const;
        Vec3   operator* (float scale) const;
        Vec3&  operator*=(float scale);
        Vec3   operator* (const Vec3& vec) const;
        Vec3&  operator*=(const Vec3& vec);
        Vec3   operator/ (const Vec3& vec) const;
        Vec3&  operator/=(const Vec3& vec);
        bool   operator==(const Vec3& vec) const;
        bool   operator!=(const Vec3& vec) const;
        float& operator[](uint i);
        #pragma endregion

        #pragma region Functions
        float   length() const;
        float   squaredLength() const;
        Vec3&   unit();
        Vec3    unit() const;
        float	angle(const Vec3& vec3) const;
        float   dot(const Vec3& vec3) const;
        Vec3    cross(const Vec3& v2) const;

        bool    equals(const Vec3& vec, float epsilon) const;
        void    round();
        Vec3    round() const;

        std::string to_string() const;
        #pragma endregion
        
        static Vec3 center(const Vec3& a, const Vec3& b);
        static Vec3 vec3FromPoints(const Vec3& v1, const Vec3& v2);
        static float angle(const Vec3& v1, const Vec3& v2);

        static Vec3 zero;
        static Vec3 one;
        static Vec3 up;
        static Vec3 down;
        static Vec3 right;
        static Vec3 left;
        static Vec3 forward;
        static Vec3 backward;
        static Vec3 infinity;
    };

    std::ostream& operator<<(std::ostream& os, const Vec3& vec);
}

#endif //__VEC3_H__

#include "Light.h"

namespace LowRenderer
{
    #pragma region Constructors
    Light::Light():
        _pos               { Vec3::zero },
        _color             { Vec3::one },
        _ambientStrength   { AMBIENT_STRENGTH },
        _specular          { SPECULAR_COLOR },
        _ambient           { _color * _ambientStrength }
    {}

    Light::Light(const Vec3& pos, const Vec3& color, float ambientStrength):
        _pos               { pos },
        _color             { color },
        _ambientStrength   { ambientStrength },
        _specular          { SPECULAR_COLOR },
        _ambient           { _color * _ambientStrength }
    {}

    Light::Light(const Light& l):
        _pos               { l._pos },
        _color             { l._color },
        _ambientStrength   { l._ambientStrength },
        _specular          { l._specular },
        _ambient           { l._ambient }
    {}
    #pragma endregion

    #pragma region Operators
    Light& Light::operator= (const Light& l)
    {
        _pos               = l._pos;
        _color             = l._color;
        _ambientStrength   = l._ambientStrength;
        _specular          = l._specular;
        _ambient           = l._ambient;

        return *this;
    }
    #pragma endregion

    #pragma region Accessors
    void Light::setColor(const Vec3& color)
    {
        // Set the colo
        _color = color;

        // Update the ambient
        _ambient  = _color * _ambientStrength;
    }

    void Light::setAmbientStrength(float str)
    {
        // Set the strength
        _ambientStrength = str;

        // Update the colors of the vectors
        _ambient  = _color * _ambientStrength;
    }
    #pragma endregion
} /* LowRenderer */

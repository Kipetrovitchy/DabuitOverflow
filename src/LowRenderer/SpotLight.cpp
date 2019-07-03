#include "SpotLight.h"

namespace LowRenderer
{
    #pragma region Constructors
    SpotLight::SpotLight():
        PointLight(),
        _direction     { DIRECTION },
        _cutOff        { CUT_OFF },
        _outerCutOff   { OUTER_CUT_OFF }
    {}

    SpotLight::SpotLight(const Vec3& pos, const Vec3& color, float ambientStrength):
        PointLight(pos, color, ambientStrength),
        _direction     { DIRECTION },
        _cutOff        { CUT_OFF },
        _outerCutOff   { OUTER_CUT_OFF }
    {}

    SpotLight::SpotLight(const Vec3& pos, const Vec3& color,
                float ambientStrength, const Vec3& attenuations):
        PointLight(pos, color, ambientStrength, attenuations),
        _direction     { DIRECTION },
        _cutOff        { CUT_OFF },
        _outerCutOff   { OUTER_CUT_OFF }
    {}

    SpotLight::SpotLight(const Vec3& pos, const Vec3& color, float ambientStrength,
                    const Vec3& attenuations, const Vec3& direction):
        PointLight(pos, color, ambientStrength, attenuations),
        _direction     { direction },
        _cutOff        { CUT_OFF },
        _outerCutOff   { OUTER_CUT_OFF }
    {}

    SpotLight::SpotLight(const Light& l):
        PointLight(l),
        _direction     { DIRECTION },
        _cutOff        { CUT_OFF },
        _outerCutOff   { OUTER_CUT_OFF }
    {}

    SpotLight::SpotLight(const PointLight& l):
        PointLight(l),
        _direction     { DIRECTION },
        _cutOff        { CUT_OFF },
        _outerCutOff   { OUTER_CUT_OFF }
    {}

    SpotLight::SpotLight(const SpotLight& l):
        PointLight(l),
        _direction     { l._direction },
        _cutOff        { l._cutOff },
        _outerCutOff   { l._outerCutOff }
    {}
    #pragma endregion

    #pragma region Operators
    SpotLight& SpotLight::operator= (const SpotLight& l)
    {
        (PointLight&)*this = l;
        _direction        = l._direction;
        _cutOff           = l._cutOff;
        _outerCutOff      = l._outerCutOff;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    Light* SpotLight::clone() const noexcept
    {
        return new SpotLight(*this);
    }
    #pragma endregion

    #pragma region Accessors
    void SpotLight::setValuesToShader(const Shader& shader, int i) const noexcept
    {
        std::string strI = std::to_string(i);

        shader.setInt   ("lights[" + strI + "].type", TYPE_SPOTLIGHT);

        // Set the position of the SpotLight
        shader.setVec3  ("lights[" + strI + "].direction", _direction);
        shader.setVec3  ("lights[" + strI + "].position", _pos);

        // Set the components of the light
        shader.setVec3  ("lights[" + strI + "].ambient", _ambient);
        shader.setVec3  ("lights[" + strI + "].diffuse", _color);
        shader.setVec3  ("lights[" + strI + "].specular", _specular);

        // Set the attenuation's values
        shader.setFloat ("lights[" + strI + "].constant", _constant);
        shader.setFloat ("lights[" + strI + "].linear",  _linear);
        shader.setFloat ("lights[" + strI + "].quadratic", _quadratic);

        // Set the attenuation's values
        shader.setFloat ("lights[" + strI + "].cutOff", _cutOff);
        shader.setFloat ("lights[" + strI + "].outerCutOff",  _outerCutOff);
    }
    #pragma endregion
} /* LowRenderer */

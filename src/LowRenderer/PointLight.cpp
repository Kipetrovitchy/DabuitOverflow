#include "PointLight.h"

namespace LowRenderer
{
    #pragma region Constructors
    PointLight::PointLight():
        Light(),
        _constant  { CONSTANT },
        _linear    { LINEAR },
        _quadratic { QUADRATIC }
    {}

    PointLight::PointLight(const Vec3& pos, const Vec3& color,
                           float ambientStrength):
        Light(pos, color, ambientStrength),
        _constant  { CONSTANT },
        _linear    { LINEAR },
        _quadratic { QUADRATIC }
    {}

    PointLight::PointLight(const Vec3& pos, const Vec3& color,
                float ambientStrength, const Vec3& attenuations):
        Light(pos, color, ambientStrength),
        _constant  { attenuations.x },
        _linear    { attenuations.y },
        _quadratic { attenuations.z }
    {}

    PointLight::PointLight(const Light& l):
        Light(l),
        _constant  { CONSTANT },
        _linear    { LINEAR },
        _quadratic { QUADRATIC }
    {}

    PointLight::PointLight(const PointLight& l):
        Light(l),
        _constant  { l._constant },
        _linear    { l._linear },
        _quadratic { l._quadratic }
    {}
    #pragma endregion

    #pragma region Operators
    PointLight& PointLight::operator= (const PointLight& l)
    {
        (Light&)*this = l;
        _constant  = l._constant;
        _linear    = l._linear;
        _quadratic = l._quadratic;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    Light*  PointLight::clone() const noexcept
    {
        return new PointLight(*this);
    }
    #pragma endregion

    #pragma region Accessors
    void PointLight::setValuesToShader(const Shader& shader, int i) const noexcept
    {
        std::string strI = std::to_string(i);

        shader.setInt   ("lights[" + strI + "].type", TYPE_POINTLIGHT);

        // Set the position of the PointLight
        shader.setVec3  ("lights[" + strI + "].position", _pos);

        // Set the components of the light
        shader.setVec3  ("lights[" + strI + "].ambient", _ambient);
        shader.setVec3  ("lights[" + strI + "].diffuse", _color);
        shader.setVec3  ("lights[" + strI + "].specular", _specular);

        // Set the attenuation's values
        shader.setFloat ("lights[" + strI + "].constant", _constant);
        shader.setFloat ("lights[" + strI + "].linear",  _linear);
        shader.setFloat ("lights[" + strI + "].quadratic", _quadratic);
    }
    #pragma endregion
} /* LowRenderer */

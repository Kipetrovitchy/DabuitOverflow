#include "DirectionalLight.h"

namespace LowRenderer
{
    #pragma region Constructors
    DirectionalLight::DirectionalLight():
        Light()
    {}

    DirectionalLight::DirectionalLight(const Vec3& pos, const Vec3& color,
                                       float ambientStrength):
        Light(pos, color, ambientStrength)
    {}

    DirectionalLight::DirectionalLight(const Light& l):
        Light(l)
    {}

    DirectionalLight::DirectionalLight(const DirectionalLight& l):
        Light(l)
    {}
    #pragma endregion

    #pragma region Operators
    DirectionalLight& DirectionalLight::operator= (const DirectionalLight& l)
    {
        (Light&)*this = l;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    Light* DirectionalLight::clone() const noexcept
    {
        return new DirectionalLight(*this);
    }

    void DirectionalLight::setValuesToShader(const Shader& shader, int i)
        const noexcept
    {
        std::string strI = std::to_string(i);

        shader.setInt   ("lights[" + strI + "].type", TYPE_DIRECTIONALLIGHT);

        // Set the position of the DirectionalLight
        shader.setVec3  ("lights[" + strI + "].direction", _pos);

        // Set the components of the light
        shader.setVec3  ("lights[" + strI + "].ambient", _ambient);
        shader.setVec3  ("lights[" + strI + "].diffuse", _color);
        shader.setVec3  ("lights[" + strI + "].specular", _specular);
    }
    #pragma endregion
} /* LowRenderer */

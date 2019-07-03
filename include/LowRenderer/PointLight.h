#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"

#define TYPE_POINTLIGHT 1

#define CONSTANT    1.0f
#define LINEAR      0.09f
#define QUADRATIC   0.032f

namespace LowRenderer
{
    class PointLight : public Light
    {
    protected:
        #pragma region Attributes
        float _constant;
        float _linear;
        float _quadratic;
        #pragma endregion

    public:
        #pragma region Constructors
        PointLight();
        PointLight(const Vec3& pos, const Vec3& color, float ambientStrength);
        PointLight(const Vec3& pos, const Vec3& color, float ambientStrength,
                    const Vec3& attenuations);
        PointLight(const Light& l);
        PointLight(const PointLight& l);
        virtual ~PointLight() = default;
        #pragma endregion

        #pragma region Operators
        PointLight& operator= (const PointLight& l);
        #pragma endregion

        #pragma region Functions
        virtual Light*  clone() const noexcept;
        virtual void    setValuesToShader(const Shader& shader, int i)
            const noexcept;
        #pragma endregion
    };
} /* LowRenderer */

#endif//__POINTLIGHT_H__

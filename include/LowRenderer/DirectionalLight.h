#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#define TYPE_DIRECTIONALLIGHT 0

#include "Light.h"

namespace LowRenderer
{
    class DirectionalLight : public Light
    {
    public:
        #pragma region Constructors
        DirectionalLight();
        DirectionalLight(const Vec3& pos, const Vec3& color, float ambientStrength);
        DirectionalLight(const Light& l);
        DirectionalLight(const DirectionalLight& l);
        virtual ~DirectionalLight() = default;
        #pragma endregion

        #pragma region Operators
        DirectionalLight& operator= (const DirectionalLight& l);
        #pragma endregion

        #pragma region Functions
        virtual Light*  clone() const noexcept;
        virtual void    setValuesToShader(const Shader& shader, int i)
            const noexcept;
        #pragma endregion
    };
} /* LowRenderer */

#endif//__DIRECTIONALLIGHT_H__

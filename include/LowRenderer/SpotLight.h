#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "PointLight.h"

#define TYPE_SPOTLIGHT  2

#define CUT_OFF         0.91f
#define OUTER_CUT_OFF   0.82f
#define DIRECTION       Vec3::forward

namespace LowRenderer
{
    class SpotLight : public PointLight {
    protected:
        #pragma region Attributes
        Vec3    _direction;
        float   _cutOff;
        float   _outerCutOff;
        #pragma endregion

    public:
        #pragma region Constructors
        SpotLight();
        SpotLight(const Vec3& pos, const Vec3& color, float ambientStrength);
        SpotLight(const Vec3& pos, const Vec3& color, float ambientStrength,
                    const Vec3& attenuations);
        SpotLight(const Vec3& pos, const Vec3& color, float ambientStrength,
                    const Vec3& attenuations, const Vec3& direction);
        SpotLight(const Light& l);
        SpotLight(const PointLight& l);
        SpotLight(const SpotLight& l);
        virtual ~SpotLight() = default;
        #pragma endregion

        #pragma region Operators
        SpotLight& operator= (const SpotLight& l);
        #pragma endregion

        #pragma region Functions
        virtual Light*  clone() const noexcept;
        virtual void    setValuesToShader(const Shader& shader, int i)
            const noexcept;
        #pragma endregion

        #pragma region Accessors
        void setDirection (const Vec3& dir) { _direction = dir; };
        #pragma endregion
    };
} /* LowRenderer */

#endif//__SPOT_LIGHT_H__

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "LibMaths.h"
#include "Shader.h"

#define AMBIENT_STRENGTH    0.2f
#define SPECULAR_COLOR      1.0f, 1.0f, 1.0f

namespace LowRenderer
{
    typedef unsigned int        uint;
    typedef Core::Maths::Vec3   Vec3;
    typedef Resources::Shader   Shader;

    class Light
    {
    protected:
        #pragma region Attributes
        // Main attributes
        Vec3    _pos;
        Vec3    _color;
        float   _ambientStrength;

        // Store the different colors
        Vec3    _specular;
        Vec3    _ambient;
        #pragma endregion

    public:
        #pragma region  Constructors
        Light();
        Light(const Vec3& pos, const Vec3& color, float ambientStrength);
        Light(const Light& l);
        virtual ~Light() = default;
        #pragma endregion

        #pragma region Operators
        Light& operator= (const Light& l);
        #pragma endregion

        #pragma region Functions
        virtual Light*  clone() const noexcept = 0;
        virtual void    setValuesToShader(const Shader& shader, int i)
            const noexcept = 0;
        #pragma endregion

        #pragma region Accessors
        void setAmbientStrength (float str);
        void setColor           (const Vec3& color);
        void setSpecular        (const Vec3& spec) { _specular = spec; };
        #pragma endregion
    };
} /* LowRenderer */
#endif//__LIGHT_H__

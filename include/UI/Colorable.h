#ifndef __COLORABLE_H__
#define __COLORABLE_H__

#include "Vec4.h"
#include "Shader.h"

namespace UI
{
    #pragma region typedefs
    typedef Core::Maths::Vec4 Vec4;
    #pragma endregion

    class Colorable
    {
        protected:
            #pragma region Attributes
            Vec4 _color;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Colorable()                     noexcept;
            Colorable(const Vec4& color)    noexcept;
            Colorable(const Colorable& c)   noexcept;
            ~Colorable() = default;
            #pragma endregion
    
            #pragma region Operators
            Colorable& operator=(const Colorable& c) noexcept;
            #pragma endregion
    
            #pragma region Methods
            Colorable& setColorShader(Resources::Shader* shader) noexcept;
            #pragma endregion

            #pragma region Accessors
            inline Vec4& color()        { return _color; }
            inline Vec4  color() const  { return _color; }
            #pragma endregion
    };
} // namespace UI

#endif // __COLORABLE_H__
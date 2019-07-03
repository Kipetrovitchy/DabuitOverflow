#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "BaseUIComponent.h"
#include "Image.h"
#include "Text.h"
#include "Quad.h"
#include "Vec4.h"
#include <functional>
#include <vector>

namespace UI
{
    #pragma region Typedefs
    typedef Core::Maths::Quad Quad;
    typedef Core::Maths::Vec4 Vec4;
    #pragma endregion
    class Button : public BaseUIComponent
    {
        private:
            #pragma region Attributes
            Image* _image;
            Text*  _text;

            //Boolean to check if mouse pointer was down over the 'hitbox' of the button
            bool _pointerDownIn;
            bool _updateDisabled;

            Vec4 _baseColor;
            Vec4 _hoverColor;
            Vec4 _clickColor;
            Vec4 _disableColor;

            std::vector<Colorable*> _targetsColor;

            std::vector<std::function<void()>> _onClick;
            #pragma endregion

            #pragma region Private Functions
            void createArea(const Mat& transform, Quad& area) noexcept;
            void invokeOnClick() noexcept;
            void updateTargetsColor(Vec4 color) noexcept;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Button();
            Button(const Button& b);
            Button(Resources::Texture* texture, Resources::Shader* imgShader,
                   Resources::Font* font, Resources::Shader* textShader);
            ~Button();
            #pragma endregion
    
            #pragma region Operators
            Button& operator=(const Button& b) noexcept;
            #pragma endregion
    
            #pragma region Methods
            Button& init(Resources::Texture* texture, Resources::Shader* imgShader,
                      Resources::Font* font, Resources::Shader* textShader)     noexcept;
            //Add a event to the button click. Must be given with lambdas
            Button& addListener(std::function<void()> func)                    noexcept;
            Button& clearListeners() noexcept;
            BaseUIComponent& update(Mat transformParent,
                                    const InputModule& module) noexcept override;
            #pragma endregion

            #pragma region Accessors
            BaseUIComponent& setWidth(GLuint width)     noexcept override;
            BaseUIComponent& setHeight(GLuint height)   noexcept override;

            Button& disableUpdate(bool state) noexcept;
            
            inline Image* image() { return _image; }
            inline Text*  text()  { return _text; }

            inline Vec4& baseColor()            { return _baseColor; }
            inline Vec4  baseColor()    const   { return _baseColor; }
            inline Vec4& hoverColor()           { return _hoverColor; }
            inline Vec4  hoverColor()   const   { return _hoverColor; }
            inline Vec4& clickColor()           { return _clickColor; }
            inline Vec4  clickColor()   const   { return _clickColor; }
            inline Vec4& disableColor()         { return _disableColor; }
            inline Vec4  disableColor() const   { return _disableColor; }

            inline std::vector<Colorable*>& targetsColor() { return _targetsColor; }
            #pragma endregion
    };    
} // namespace UI

#endif // __BUTTON_H__
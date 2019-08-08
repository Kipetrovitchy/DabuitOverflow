#ifndef __INPUTMODULE_H__
#define __INPUTMODULE_H__

#include "Vec2.h"

#ifdef _WIN32
typedef unsigned int uint;
#endif

namespace Game::Inputs
{
    #pragma region Typedefs
    typedef Core::Maths::Vec2 Vec2;
    #pragma endregion

    class InputModule
    {
        private:
            #pragma region Attributes
            bool _submit;
            bool _cancel;

            Vec2 _mousePos;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            InputModule()                       noexcept;
            InputModule(const InputModule& im)  noexcept;
            ~InputModule() = default;
            #pragma endregion
    
            #pragma region Operators
            InputModule& operator=(const InputModule& im) noexcept;
            #pragma endregion
    
            #pragma region Methods
            InputModule& update(uint width, uint height) noexcept;
            #pragma endregion

            #pragma region Accessors
            inline bool     submit()    const { return _submit; }
            inline bool&    submit()          { return _submit; }

            inline bool     cancel()    const { return _cancel; }
            inline bool&    cancel()          { return _cancel; }

            inline Vec2     mousePos()  const { return _mousePos; }
            inline Vec2&    mousePos()        { return _mousePos; }
            #pragma endregion
    };
} // namespace Game::Inputs

#endif // __INPUTMODULE_H__
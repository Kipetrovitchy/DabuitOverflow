#include "InputModule.h"
#include <SDL2/SDL.h>

namespace Game::Inputs
{
    #pragma region Constructors / Destructors
    InputModule::InputModule() noexcept :
        _submit { false },
        _cancel { false },
        _mousePos { 0.f, 0.f }
    {}

    InputModule::InputModule(const InputModule& im) noexcept :
        _submit { im._submit },
        _cancel { im._cancel },
        _mousePos { im._mousePos }
    {}
    #pragma endregion

    #pragma region Operators
    InputModule& InputModule::operator=(const InputModule& im) noexcept
    {
        _submit = im._submit;
        _cancel = im._cancel;
        _mousePos = im._mousePos;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    InputModule& InputModule::update(uint width, uint height) noexcept
    {  
        int x, y;
        SDL_GetMouseState(&x, &y);
        _mousePos.x = x - width / 2.f;;
        _mousePos.y = height - y;
        

        _submit = false;
        _cancel = false;

        return *this;
    }
    #pragma endregion
} // namespace Game::Inputs

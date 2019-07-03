#include "InputMgr.h"

#include "Window.h"
#include "Player.h"
#include "Command.h"
#include "PlayerForwardCommand.h"
#include "PlayerBackwardCommand.h"
#include "PlayerLeftCommand.h"
#include "PlayerRightCommand.h"
#include "PlayerJumpCommand.h"
#include "PlayerShootCommand.h"
#include "PlayerReloadCommand.h"
#include "PlayerWeaponUpCommand.h"
#include "PlayerWeaponDownCommand.h"
#include "PlayerHealCommand.h"
#include "PlayerAimCommand.h"
#include "SubmitCommand.h"
#include "CancelCommand.h"
#include <SDL2/SDL.h>

typedef Game::Window Window;

namespace Game::Inputs
{
    InputMgr::InputMgr()
    {
        _width = 1024;
        _height= 600;
        _sdlKeyMap[SDL_SCANCODE_F1]  = Key::F1;
        _sdlKeyMap[SDL_SCANCODE_F2]  = Key::F2;
        _sdlKeyMap[SDL_SCANCODE_F3]  = Key::F3;
        _sdlKeyMap[SDL_SCANCODE_F4]  = Key::F4;
        _sdlKeyMap[SDL_SCANCODE_F5]  = Key::F5;
        _sdlKeyMap[SDL_SCANCODE_F6]  = Key::F6;
        _sdlKeyMap[SDL_SCANCODE_F7]  = Key::F7;
        _sdlKeyMap[SDL_SCANCODE_F8]  = Key::F8;
        _sdlKeyMap[SDL_SCANCODE_F9]  = Key::F9;
        _sdlKeyMap[SDL_SCANCODE_F10] = Key::F10;
        _sdlKeyMap[SDL_SCANCODE_F11] = Key::F11;
        _sdlKeyMap[SDL_SCANCODE_F12] = Key::F12;

        for (uint i = 0; i < SDL_SCANCODE_Z - SDL_SCANCODE_A; ++i)
        {
            _sdlKeyMap[SDL_SCANCODE_A + i] = (Key)((uint)(Key::A) + i);
        }

        _sdlKeyMap[SDL_SCANCODE_SPACE]      = Key::SPACE;
        _sdlKeyMap[SDL_SCANCODE_BACKSPACE]  = Key::BACKSPACE;
        _sdlKeyMap[SDL_SCANCODE_ESCAPE]     = Key::ESCAPE;
        _sdlKeyMap[SDL_SCANCODE_RETURN]     = Key::RETURN;
        _sdlKeyMap[SDL_SCANCODE_TAB]        = Key::TAB;

        _sdlKeyMap[SDL_BUTTON_LEFT + 100]   = Key::MLEFT;
        _sdlKeyMap[SDL_BUTTON_MIDDLE + 100] = Key::MMIDDLE;
        _sdlKeyMap[SDL_BUTTON_RIGHT + 100]  = Key::MRIGHT;
        _sdlKeyMap[SDL_BUTTON_X1 + 100]     = Key::MX1;
        _sdlKeyMap[SDL_BUTTON_X2 + 100]     = Key::MX2;
        _sdlKeyMap[300] = Key::MSCROLLUP;
        _sdlKeyMap[301] = Key::MSCROLLDOWN;
        resetKeys();
    } 

    InputMgr::~InputMgr()
    {
        for (auto it = _commands.begin(); it != _commands.end(); ++it)
        {
            if (it->first)
                delete it->first;
        }
    }

    InputMgr& InputMgr::init(Game::Player& p)
    {
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerForwardCommand(&p.stateMachine()),
             std::vector<Key> { Key::W })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerBackwardCommand(&p.stateMachine()),
             std::vector<Key> { Key::S })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerLeftCommand(&p.stateMachine()),
             std::vector<Key> { Key::A })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerRightCommand(&p.stateMachine()),
             std::vector<Key> { Key::D})
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerJumpCommand(&p.stateMachine()),
             std::vector<Key> { Key::SPACE })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::CancelCommand(&_module),
             std::vector <Key> { Key::ESCAPE })
        );

        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerShootCommand(&p.stateMachine()),
             std::vector<Key> { Key::MLEFT })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::SubmitCommand(&_module),
             std::vector<Key> { Key::MLEFT })
        );

        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerReloadCommand(&p.stateMachine()),
             std::vector<Key> { Key::R })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerHealCommand(&p.stateMachine()),
             std::vector<Key> { Key::H })
        );

        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerWeaponUpCommand(&p.stateMachine()),
             std::vector<Key> { Key::MSCROLLUP })
        );
        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerWeaponDownCommand(&p.stateMachine()),
             std::vector<Key> { Key::MSCROLLDOWN })
        );

        _commands.insert(
            std::pair<Commands::Command*, std::vector<Key>>
            (new Commands::PlayerAimCommand(&p.stateMachine()),
             std::vector<Key> { Key::MRIGHT })
        );

        return *this;
    }

    InputMgr& InputMgr::resize(GLuint w, GLuint h)
    {
        _width = w;
        _height = h;

        return *this;
    }

    bool InputMgr::processEvents(Game::Window* window)
    {
        _module.update(_width, _height);
        SDL_Event event;

        //reset the mouse scroll events
        auto itScroll = _sdlKeyMap.find(300);
        _pressedKeys[(size_t)itScroll->second] = false;
        itScroll = _sdlKeyMap.find(301);
        _pressedKeys[(size_t)itScroll->second] = false;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                window->simulation().quit();
                return false;

            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    window->reshape(event.window.data1, event.window.data2);
                    break;
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                auto itSdlKey = _sdlKeyMap.find(event.key.keysym.scancode);
                if (itSdlKey != _sdlKeyMap.end())
                {
                    _pressedKeys[(size_t)itSdlKey->second] = true;
                }
            } 
            break;

            case SDL_KEYUP:
            {
                auto itSdlKey = _sdlKeyMap.find(event.key.keysym.scancode);
                if (itSdlKey != _sdlKeyMap.end())
                {
                    _pressedKeys[(size_t)itSdlKey->second] = false;
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                auto itSdlKey = _sdlKeyMap.find(event.button.button + 100);
                if (itSdlKey != _sdlKeyMap.end())
                {
                    _pressedKeys[(size_t)itSdlKey->second] = true;
                }
            }
            break;
    
            case SDL_MOUSEBUTTONUP:
            {
                auto itSdlKey = _sdlKeyMap.find(event.button.button + 100);
                if (itSdlKey != _sdlKeyMap.end())
                {
                    _pressedKeys[(size_t)itSdlKey->second] = false;
                }
            }
            break;

            case SDL_MOUSEWHEEL:
            {
                if (event.wheel.y > 0)
                {
                    auto itSdlKey = _sdlKeyMap.find(300);
                    _pressedKeys[(size_t)itSdlKey->second] = true;
                }
                else if (event.wheel.y < 0)
                {
                    auto itSdlKey = _sdlKeyMap.find(301);
                    _pressedKeys[(size_t)itSdlKey->second] = true;
                }
            }
            }
        }

        executeCommands();

        return true;
    }

    InputMgr& InputMgr::executeCommands() noexcept
    {
        //Execute key commands
        for (auto itCmd = _commands.begin(); itCmd != _commands.end(); ++itCmd)
        {
            if (itCmd->first && itCmd->first->enabled())
            {
                for (auto itKey = itCmd->second.begin(); itKey != itCmd->second.end(); ++itKey)
                {
                    if (_pressedKeys[(uint)(*itKey)])
                    {
                        itCmd->first->execute();
                        break;
                    }
                }
            } 
        }

        return *this;
    }
    InputMgr& InputMgr::resetKeys()
    {
        for (size_t i = 0; i < (size_t)Key::COUNT; ++i)
        {
            _pressedKeys[i] = false;
        }

        return *this;
    }

    bool InputMgr::isPressingKey(Key key)  const
    {
        return _pressedKeys[(size_t)key];
    }

    InputMgr& InputMgr::disablePlayerCommands()
    {
        Commands::PlayerCommand* command;

        for (auto it = _commands.begin(); it != _commands.end(); ++it)
        {
            command = dynamic_cast<Commands::PlayerCommand*>(it->first);
            if (command)
                command->enabled() = false;
        }

        return *this;
    }

    InputMgr& InputMgr::enablePlayerCommands()
    {
        Commands::PlayerCommand* command;

        for (auto it = _commands.begin(); it != _commands.end(); ++it)
        {
            command = dynamic_cast<Commands::PlayerCommand*>(it->first);
            if (command)
                command->enabled() = true;
        }

        return *this;
    }

    InputMgr& InputMgr::disableAllCommands()
    {
        for (auto it = _commands.begin(); it != _commands.end(); ++it)
        {
            if (it->first)
                it->first->enabled() = false;
        }

        return *this;
    }

    InputMgr& InputMgr::enableAllCommands()
    {
        for (auto it = _commands.begin(); it != _commands.end(); ++it)
        {
            if (it->first)
                it->first->enabled() = true;
        }

        return *this;
    }
}


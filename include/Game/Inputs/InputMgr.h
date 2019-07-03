#ifndef __INPUT_MGR_H__
#define __INPUT_MGR_H__

#include <unordered_map>
#include <GL/glew.h>
#include <vector>
#include "Command.h"
#include "InputModule.h"

enum class Key : unsigned int
{
    F1 = 0, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    RETURN, ESCAPE, BACKSPACE, TAB, SPACE, 

    MLEFT,
    MMIDDLE,
    MRIGHT,
    MX1,
    MX2,
    MSCROLLDOWN,
    MSCROLLUP,
    COUNT,
};
namespace Game
{

    class Player;
    class Window;
} // namespace Game

namespace Game::Inputs
{

    
    class InputMgr
    {
        private:
            #pragma region Attributes
            std::unordered_map<unsigned int, Key>	                    _sdlKeyMap;
            std::unordered_map<Commands::Command*, std::vector<Key> >   _commands;
            bool    _pressedKeys[(size_t)Key::COUNT];

            InputModule _module;
            GLuint _width;
            GLuint _height;
            #pragma endregion

            #pragma region Function
            InputMgr& resetKeys();
            InputMgr& executeCommands() noexcept;
            #pragma endregion

        public:
            #pragma region Constructors
            InputMgr();
            InputMgr(const InputMgr& im);
            ~InputMgr();
            #pragma endregion

            #pragma region Operators
            InputMgr& operator=(const InputMgr& im);
            #pragma endregion

            #pragma region Functions
            InputMgr& init(Game::Player& p);
            InputMgr& resize(GLuint w, GLuint h);
            bool processEvents(Game::Window* window);
            bool isPressingKey(Key key) const;

            InputMgr& disablePlayerCommands();
            InputMgr& enablePlayerCommands();

            InputMgr& disableAllCommands();
            InputMgr& enableAllCommands();
            #pragma endregion

            #pragma region Accessors
            inline InputModule module() const { return _module; }
            #pragma endregion
    };
} // Player

#endif//__INPUT_MGR_H__
#ifndef __GAME_OVER_MSGS_H__
#define __GAME_OVER_MSGS_H__

#include "Text.h"
#include "Image.h"
#include "Canvas.h"
#include "ResourcesManager.h"

namespace UI
{
    #pragma region typedefs
    typedef Resources::Canvas           Canvas;
    typedef Resources::ResourcesManager ResourcesManager;
    #pragma endregion
    class GameOverMsgs
    {
    private:
        #pragma region Attributes
        Text* _winMsg;
        Text* _looseMsg;
        Image* _bg;

        //Cooldown while the corresponding message is shown before going back to the Menu
        float _baseCdShown;
        float _cd;
        #pragma endregion
    public:
        #pragma region Constructors / Desctructors
        GameOverMsgs()                          noexcept;
        GameOverMsgs(ResourcesManager* mgr, Canvas* hud, float cd) noexcept;
        GameOverMsgs(const GameOverMsgs& copy)  noexcept;
        ~GameOverMsgs() = default;
        #pragma endregion

        #pragma region Operators
        GameOverMsgs& operator=(const GameOverMsgs& copy) noexcept;
        #pragma endregion

        #pragma region Methods
        GameOverMsgs& init(ResourcesManager* mgr, Canvas* hud, float cd);

        GameOverMsgs& showWin() noexcept;
        GameOverMsgs& showLoose() noexcept;

        bool updateWin(float deltatime) noexcept;
        bool updateLoose(float deltatime) noexcept;
        #pragma endregion

        #pragma region Accessors
        inline bool isWin() const { return _winMsg->enabled(); }
    };
    
} // namespace UI

#endif // __GAME_OVER_MSGS_H__
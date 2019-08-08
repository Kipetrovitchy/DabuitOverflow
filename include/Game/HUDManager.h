#ifndef __HUDMANAGER_H__
#define __HUDMANAGER_H__

#include "Image.h"
#include "Text.h"
#include "Button.h"
#include "ResourcesManager.h"
#include "Player.h"
#include "GraphCanvas.h"
#include "LifeBar.h"
#include "GameOverMsgs.h"
#include "Johan.h"
#include "LevelManager.h"

#if defined(__linux__)
	#define TEXT_VERTEX ".\\resources\\Shaders\\text.vsh"
	#define TEXT_FRAGMENT ".\\resources\\Shaders\\text.fsh"
	#define IMG_VERTEX ".\\resources\\Shaders\\image.vs"
	#define IMG_FRAGMENT ".\\resources\\Shaders\\image.fs"
	#define BUTTON_IMG ".\\resources\\button.png"
	#define BG_IMG ".\\resources\\bg.png"
	#define OUTLINE_IMG ".\\resources\\outline.png"
	#define CROSS_IMG ".\\resources\\cross.png"
	#define MEDKIT_IMG ".\\resources\\Items\\medkit.png"
	#define TEXT_FONT ".\\resources\\ProductSans-Medium.ttf"
#elif _WIN32
	#define TEXT_VERTEX "./resources/Shaders/text.vsh"
	#define TEXT_FRAGMENT "./resources/Shaders/text.fsh"
	#define IMG_VERTEX "./resources/Shaders/image.vs"
	#define IMG_FRAGMENT "./resources/Shaders/image.fs"
	#define BUTTON_IMG "./resources/button.png"
	#define BG_IMG "./resources/bg.png"
	#define OUTLINE_IMG "./resources/outline.png"
	#define CROSS_IMG "./resources/cross.png"
	#define MEDKIT_IMG "./resources/Items/medkit.png"
	#define TEXT_FONT "./resources/ProductSans-Medium.ttf"
#endif

namespace Game
{
    #pragma region enum
    enum class EMenuState : unsigned int
    {
        NONE = 0,

        MAIN,
        ESCAPE,
        OPTIONS,
        KEYBINDS,
        INVENTORY
    };
    #pragma endregion
    class GameMgr;

    #pragma region Typedefs
    typedef UI::Image                           Image;
    typedef UI::Button                          Button;
    typedef UI::GameOverMsgs                    GameOverMsgs;
    typedef UI::Text                            Text;
    typedef UI::LifeBar                         LifeBar;
    typedef UI::Johan                           Johan;
    typedef Resources::ResourcesManager         ResourcesManager;
    typedef Core::DataStructure::GraphCanvas    GraphCanvas;
    #pragma endregion

    class HUDManager
    {
        private:
            #pragma region Attributes
            Button*         _loadGame;
            Image*          _weapon;
            Image*          _medkit;
            Text*           _ammoInClip;
            Text*           _ammoTotal;
            Text*           _enemyLeft;
            LifeBar         _lifeBar;
            GameOverMsgs   _gameOverMsgs;

            Johan           _johan;
            bool            _winOnce;

            EMenuState _menuState;
            EMenuState _lastMenuState;
            #pragma endregion

            #pragma region Private Functions
            void createMainMenu(GameMgr* game, ResourcesManager* mgr,
                                GraphCanvas& graph);
            void createEscMenu(GameMgr* game, ResourcesManager* mgr,
                               GraphCanvas& graph);
            void createOptionsMenu(GameMgr* game, ResourcesManager* mgr,
                                   GraphCanvas& graph);
            void createHUD(GameMgr* game, ResourcesManager* mgr,
                           GraphCanvas& graph);

            void updateWeapon(Weapon* mainWeapon) noexcept;
            void updateHP(int actual, int max) noexcept;
            void updateAmmo(int inClip, int inInventory) noexcept;
            void updateMedkit(bool state) noexcept;
            void updateEnemiesLeft(int left) noexcept;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            HUDManager()               noexcept;
            HUDManager(const HUDManager& hud) noexcept;
            ~HUDManager() = default;
            #pragma endregion
    
            #pragma region Operators
            HUDManager& operator=(const HUDManager& hud) noexcept;
            #pragma endregion
    
            #pragma region Methods
            HUDManager& init(GameMgr* game, ResourcesManager* mgr,
                             GraphCanvas& graph, Player& player, LevelManager& lm) noexcept;

            HUDManager& updateMenuState(EMenuState state) noexcept;
            HUDManager& update(float deltatime) noexcept;
            #pragma endregion

            #pragma region Accessors
            inline Button* loadGameButton() const { return _loadGame; }

            inline GameOverMsgs& gameOverMsgs() { return _gameOverMsgs; }
            inline EMenuState menuState() const { return _menuState; };
            inline EMenuState lastMenuState() const { return _lastMenuState; };
            #pragma endregion
    };
} // namespace Game

#endif // __HUDMANAGER_H__
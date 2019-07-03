#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "Enemy.h"
#include "Player.h"
#include "GameOverMsgs.h"

namespace Game
{
    class LevelManager
    {
        private:
            #pragma region Attributes
            bool _showWin;
            bool _showLoose;
            std::function<void(int)> _updateEnemiesLeft;
            Player* _player;
            std::vector<Enemy*> _enemies;

            //UI part of the level that will show the win or loose 
            //depending of the conditions
            UI::GameOverMsgs* _gameOverMsgs;
            #pragma endregion

            #pragma region Private Functions
            void checkEnemiesDeath(Scene& scene) noexcept;
            void updateEnemiesLeft() noexcept;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            LevelManager()                                          noexcept;
            LevelManager(Player* player, UI::GameOverMsgs* msgs)    noexcept;
            LevelManager(const LevelManager& lm)                    noexcept;
            ~LevelManager() = default;
            #pragma endregion

            #pragma region Accessors
                inline std::vector<Enemy*>& enemies() {return _enemies;};
            #pragma endregion
    
            #pragma region Operators
            LevelManager& operator=(const LevelManager& lm) noexcept;
            #pragma endregion
    
            #pragma region Methods
            LevelManager& addEnemy(Enemy* enemy)                        noexcept;
            LevelManager& setPlayer(Player* player)                     noexcept;
            LevelManager& setGameOverMsgs(UI::GameOverMsgs* gameOver)   noexcept;
            LevelManager& setUpdateEnemiesLeft(std::function<void(int)> func) noexcept;

            //Return true if the cooldown for the message is done
            LevelManager& update(Scene& scene) noexcept;
            bool showMessage(float deltatime) noexcept;
            #pragma endregion

            #pragma region Accessors
            bool showWin() const { return _showWin; }
            bool showLoose() const { return _showLoose; }
            #pragma endregion
    };
} // namespace Game

#endif // __LEVEL_MANAGER_H__
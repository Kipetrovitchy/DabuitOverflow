#include "LevelManager.h"

namespace Game
{
    #pragma region Constructors / Destructors
    LevelManager::LevelManager() noexcept :
        _showWin { false },
        _showLoose { false },
        _player { nullptr },
        _gameOverMsgs { nullptr }
    {}

    LevelManager::LevelManager(Player* player, UI::GameOverMsgs* msgs) noexcept :
        _showWin { false },
        _showLoose { false },
        _player { player },
        _gameOverMsgs { msgs }
    {}
    
    LevelManager::LevelManager(const LevelManager& lm) noexcept :
        _showWin { lm._showWin },
        _showLoose { lm._showLoose },
        _player { lm._player },
        _enemies { lm._enemies },
        _gameOverMsgs { lm._gameOverMsgs }
    {}
    #pragma endregion

    #pragma region Operators
    LevelManager& LevelManager::operator=(const LevelManager& lm) noexcept
    {
        _showWin = lm._showWin;
        _showLoose = lm._showLoose;
        _player = lm._player;
        _enemies = lm._enemies;
        _gameOverMsgs = lm._gameOverMsgs;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    LevelManager& LevelManager::addEnemy(Enemy* enemy) noexcept
    {
        _enemies.push_back(enemy);

        updateEnemiesLeft();

        return *this;
    }

    LevelManager& LevelManager::setPlayer(Player* player) noexcept
    {
        _player = player;

        return *this;
    }

    LevelManager& LevelManager::setGameOverMsgs(UI::GameOverMsgs* gameOver) noexcept
    {
        _gameOverMsgs = gameOver;

        return *this;
    }

    LevelManager& LevelManager::setUpdateEnemiesLeft(std::function<void(int)> func) noexcept
    {
        _updateEnemiesLeft = func;

        updateEnemiesLeft();

        return *this;
    }

    void LevelManager::updateEnemiesLeft() noexcept
    {
        _updateEnemiesLeft(_enemies.size());
    }


    LevelManager& LevelManager::update(Scene& scene) noexcept
    {
        //Check the player death to show the loose message
        if (_player->isDead())
        {
            _showLoose = true;
            _gameOverMsgs->showLoose();
        }
        //Check the enemies left in the map to show the win message
        checkEnemiesDeath(scene);

        return *this;
    }

    bool LevelManager::showMessage(float deltatime) noexcept
    {
        if (_showLoose)
        {
            //return true if the cooldown is over
            if (_gameOverMsgs->updateLoose(deltatime))
            {
                _showLoose = false;
                return true;   
            }      
        }
        else if (_showWin)
        {
            //return true if the cooldown is over
            if (_gameOverMsgs->updateWin(deltatime))
            {
                _showWin = false;
                return true;   
            }
        }
        
        return false;
    }
    #pragma endregion

    #pragma region Private Functions
    void LevelManager::checkEnemiesDeath(Scene& scene) noexcept
    {
        for (auto it = _enemies.begin(); it != _enemies.end();)
        {
            if ((*it) && (*it)->isDead())
            {
                scene.remove(*it);
                it = _enemies.erase(it);
                updateEnemiesLeft();
            }
            else
                ++it;
        }

        if (_enemies.empty())
        {
            _showWin = true;
            _gameOverMsgs->showWin();
        }
    }
    #pragma endregion
} // namespace Game

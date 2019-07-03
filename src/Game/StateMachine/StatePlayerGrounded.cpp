#include "StatePlayerGrounded.h"
#include "Transition.h"
#include "Player.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StatePlayerGrounded::StatePlayerGrounded():
        StatePlayer()
    {}

    StatePlayerGrounded::StatePlayerGrounded(const StatePlayerGrounded& sp):
        StatePlayer(sp)
    {}

    StatePlayerGrounded::StatePlayerGrounded(Player* p):
        StatePlayer(p)
    {}

    StatePlayerGrounded::StatePlayerGrounded(Player* p, const std::vector<Transition*>& transitions):
        StatePlayer(p, transitions)
    {}
    #pragma endregion

    #pragma region Operators
    StatePlayerGrounded& StatePlayerGrounded::operator=(const StatePlayerGrounded& sp) noexcept
    {
        _player = sp._player;
        for (Transition* t : sp._transitions)
            _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StatePlayerGrounded::update(Scene& scene, float deltaTime) noexcept
    {
        _player->updateIsGroundedValue(scene);
        
        _player->move(deltaTime);
        _player->tryJump();

        _player->tryShoot(scene);
        _player->tryReload();
        _player->tryHeal();
        _player->tryAim(deltaTime);

        return *this;
    }

    StatePlayer& StatePlayerGrounded::moveForward() noexcept
    {
        _player->moveForward();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::moveBackward() noexcept
    {
        _player->moveBackward();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::moveRight() noexcept
    {
        _player->moveRight();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::moveLeft() noexcept
    {
        _player->moveLeft();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::jump() noexcept
    {
        _player->jump();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::shoot() noexcept
    {
        _player->shoot();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::reload() noexcept
    {
        _player->reload();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::changeWeapon(int dir) noexcept
    {
        _player->changeWeapon(dir);

        return *this;
    }
    StatePlayer& StatePlayerGrounded::heal() noexcept
    {
        _player->heal();

        return *this;
    }
    StatePlayer& StatePlayerGrounded::aim() noexcept
    {
        _player->aim();

        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine

#include "StatePlayerFlying.h"
#include "Transition.h"
#include "Player.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StatePlayerFlying::StatePlayerFlying():
        StatePlayer()
    {}

    StatePlayerFlying::StatePlayerFlying(const StatePlayerFlying& sp):
        StatePlayer(sp)
    {}

    StatePlayerFlying::StatePlayerFlying(Player* p) :
        StatePlayer(p)
    {}

    StatePlayerFlying::StatePlayerFlying(Player* p, const std::vector<Transition*>& transitions):
        StatePlayer(p, transitions)
    {}
    #pragma endregion

    #pragma region Operators
    StatePlayerFlying& StatePlayerFlying::operator=(const StatePlayerFlying& sp) noexcept
    {
        _player = sp._player;
        for (Transition* t : sp._transitions)
            _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StatePlayerFlying::update(Scene& scene,float deltaTime) noexcept
    {
        _player->updateIsGroundedValue(scene);

        _player->move(deltaTime);

        _player->tryShoot(scene);
        _player->tryReload();
        _player->tryHeal();
        _player->tryAim(deltaTime);

        return *this;
    }

    StatePlayer& StatePlayerFlying::moveForward() noexcept
    {
        _player->moveForward();

        return *this;
    }
    StatePlayer& StatePlayerFlying::moveBackward() noexcept
    {
        _player->moveBackward();

        return *this;
    }
    StatePlayer& StatePlayerFlying::moveRight() noexcept
    {
        _player->moveRight();

        return *this;
    }
    StatePlayer& StatePlayerFlying::moveLeft() noexcept
    {
        _player->moveLeft();

        return *this;
    }
    StatePlayer& StatePlayerFlying::jump() noexcept
    {
        return *this;
    }
    StatePlayer& StatePlayerFlying::shoot() noexcept
    {
        _player->shoot();

        return *this;
    }
    StatePlayer& StatePlayerFlying::reload() noexcept
    {
        _player->reload();

        return *this;
    }
    StatePlayer& StatePlayerFlying::changeWeapon(int dir) noexcept
    {
        _player->changeWeapon(dir);

        return *this;
    }
    StatePlayer& StatePlayerFlying::heal() noexcept
    {
        _player->heal();

        return *this;
    }
    StatePlayer& StatePlayerFlying::aim() noexcept
    {
        _player->aim();

        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine

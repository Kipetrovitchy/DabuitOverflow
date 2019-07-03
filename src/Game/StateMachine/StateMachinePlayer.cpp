#include "StateMachinePlayer.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StateMachinePlayer::StateMachinePlayer() :
        StateMachine()
    {
        if (_currentState)
            _playerState = dynamic_cast<StatePlayer*>(_currentState);
    }

    StateMachinePlayer::StateMachinePlayer(const StateMachinePlayer& sm) :
        StateMachine(sm)
    {
        if (_currentState)
            _playerState = dynamic_cast<StatePlayer*>(_currentState);
    }

    StateMachinePlayer::StateMachinePlayer(State* s) :
        StateMachine(s)
    {
        if (_currentState)
            _playerState = dynamic_cast<StatePlayer*>(_currentState);
    }
    #pragma endregion

    #pragma region Operators
    StateMachinePlayer& StateMachinePlayer::operator=(const StateMachinePlayer& sm)
    {
        StateMachine::operator=(sm);
        if (_currentState)
            _playerState = dynamic_cast<StatePlayer*>(_currentState);

        return *this;
    }
    #pragma endregion

    #pragma region Functions
        StateMachinePlayer& StateMachinePlayer::init(IController* c) noexcept
        {
            _playerState->init(c);

            return *this;
        }

        StateMachine& StateMachinePlayer::update(Scene& scene, float deltaTime) noexcept
        {
            _playerState->update(scene, deltaTime);

            StateMachine::checkTransition();
            
            return *this;
        }

        StateMachine& StateMachinePlayer::changeState(State* state) noexcept
        {
            StateMachine::changeState(state);

            if (_currentState)
                _playerState = dynamic_cast<StatePlayer*>(_currentState);

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::moveForward() noexcept
        {
            _playerState->moveForward();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::moveBackward() noexcept
        {
            _playerState->moveBackward();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::moveLeft() noexcept
        {
            _playerState->moveLeft();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::moveRight() noexcept
        {
            _playerState->moveRight();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::jump() noexcept
        {
            _playerState->jump();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::shoot() noexcept
        {
            _playerState->shoot();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::reload() noexcept
        {
            _playerState->reload();

            return *this;
        }
        
        StateMachinePlayer& StateMachinePlayer::changeWeapon(int dir) noexcept
        {
            _playerState->changeWeapon(dir);

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::heal() noexcept
        {
            _playerState->heal();

            return *this;
        }

        StateMachinePlayer& StateMachinePlayer::aim() noexcept
        {
            _playerState->aim();

            return *this;
        }
    #pragma endregion
} // namespace Game::StateMachine

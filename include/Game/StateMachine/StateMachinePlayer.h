#ifndef __STATE_MACHINE_PLAYER_H__
#define __STATE_MACHINE_PLAYER_H__

#include "StateMachine.h"
#include "StatePlayer.h"

namespace Game::StateMachines
{
    #pragma region Typedefs
        typedef Resources::Scene    Scene;
    #pragma endregion

    class StateMachinePlayer : public StateMachine
    {
        protected:
            #pragma region Attributes
                StatePlayer* _playerState; 
            #pragma endregion

        public:
            #pragma region Constructors
            StateMachinePlayer();
            StateMachinePlayer(const StateMachinePlayer& sm);
            StateMachinePlayer(State* s);
            virtual ~StateMachinePlayer() = default;
            #pragma endregion

            #pragma region Operators
            StateMachinePlayer& operator=(const StateMachinePlayer& sm);
            #pragma endregion

            #pragma region Functions
            StateMachine& update(Scene& scene, float deltaTime) noexcept override;
            StateMachine& changeState(State*) noexcept override;

            StateMachinePlayer& init(IController* c)    noexcept;
            StateMachinePlayer& moveForward()           noexcept;
            StateMachinePlayer& moveBackward()          noexcept;
            StateMachinePlayer& moveLeft()              noexcept;
            StateMachinePlayer& moveRight()             noexcept;
            StateMachinePlayer& jump()                  noexcept;
            StateMachinePlayer& shoot()                 noexcept;
            StateMachinePlayer& reload()                noexcept;
            StateMachinePlayer& changeWeapon(int dir)   noexcept;
            StateMachinePlayer& heal()                  noexcept;
            StateMachinePlayer& aim()                   noexcept;
            #pragma endregion
    };
} // namespace  Game::StateMachine

#endif //__STATE_MACHINE_PLAYER_H__
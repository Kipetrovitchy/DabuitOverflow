#ifndef __STATE_PLAYER_H__
#define __STATE_PLAYER_H__

#include <vector>
#include "IController.h"
#include "GameObject.h"
#include "State.h"

namespace Game 
{
    class Player;
}
namespace Game::StateMachines
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject     GameObject;
    typedef Resources::Scene            Scene;
    #pragma endregion


    class StatePlayer : public State
    {
        protected:
            #pragma region Attributes
            Player* _player;
            #pragma endregion
    
        public:
            #pragma region Constructors
            StatePlayer();
            StatePlayer(const StatePlayer& sp);
            StatePlayer(Player* p);
            StatePlayer(Player* p, const std::vector<Transition*>& transitions);
            virtual ~StatePlayer() = default;
            #pragma endregion

            #pragma region Operators
            StatePlayer& operator=(const StatePlayer& sp) noexcept;
            #pragma endregion
    
            #pragma region Functions
            State& init(IController* c) noexcept override final;
            virtual State& update(Scene& scene, float deltaTime)    noexcept = 0;
            virtual StatePlayer& moveForward()                      noexcept = 0;
            virtual StatePlayer& moveBackward()                     noexcept = 0;
            virtual StatePlayer& moveRight()                        noexcept = 0;
            virtual StatePlayer& moveLeft()                         noexcept = 0;
            virtual StatePlayer& jump()                             noexcept = 0;
            virtual StatePlayer& shoot()                            noexcept = 0;
            virtual StatePlayer& reload()                           noexcept = 0;
            virtual StatePlayer& changeWeapon(int dir)              noexcept = 0;
            virtual StatePlayer& heal()                             noexcept = 0;
            virtual StatePlayer& aim()                              noexcept = 0;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_PLAYER_H__
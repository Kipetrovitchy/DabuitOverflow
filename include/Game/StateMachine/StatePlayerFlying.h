#ifndef __STATE_PLAYER_FLYING_H__
#define __STATE_PLAYER_FLYING_H__

#include "IController.h"
#include "GameObject.h"
#include "StatePlayer.h"

namespace Game::StateMachines
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject     GameObject;
    typedef Resources::Scene            Scene;
    #pragma endregion

    class StatePlayerFlying : public StatePlayer
    {
    
        public:
            #pragma region Constructors
            StatePlayerFlying();
            StatePlayerFlying(const StatePlayerFlying& sp);
            StatePlayerFlying(Player* p);
            StatePlayerFlying(Player* p, const std::vector<Transition*>& transitions);
            ~StatePlayerFlying() = default;
            #pragma endregion

            #pragma region Operators
            StatePlayerFlying& operator=(const StatePlayerFlying& sp) noexcept;
            #pragma endregion
    
            #pragma region Functions
            State&       update(Scene& scene, float deltaTime)  noexcept override;
            StatePlayer& moveForward()                          noexcept override;
            StatePlayer& moveBackward()                         noexcept override;
            StatePlayer& moveRight()                            noexcept override;
            StatePlayer& moveLeft()                             noexcept override;
            StatePlayer& jump()                                 noexcept override;
            StatePlayer& shoot()                                noexcept override;
            StatePlayer& reload()                               noexcept override;
            StatePlayer& changeWeapon(int dir)                  noexcept override;
            StatePlayer& heal()                                 noexcept override;
            StatePlayer& aim()                                  noexcept override;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_PLAYER_FLYING_H__
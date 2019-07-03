#ifndef __STATE_ENEMY_CHASE_H__
#define __STATE_ENEMY_CHASE_H__

#include <vector>
#include "IController.h"
#include "GameObject.h"
#include "StateEnemy.h"

namespace Game::StateMachines
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject     GameObject;
    typedef Resources::Scene            Scene;
    #pragma endregion

    class StateEnemyChase : public StateEnemy
    {
        public:
            #pragma region Constructors
            StateEnemyChase();
            StateEnemyChase(const StateEnemyChase& se);
            StateEnemyChase(Enemy* e);
            StateEnemyChase(Enemy* e, const std::vector<Transition*>& transitions);
            virtual ~StateEnemyChase() = default;
            #pragma endregion

            #pragma region Operators
            StateEnemyChase& operator=(const StateEnemyChase& se) noexcept;
            #pragma endregion
    
            #pragma region Functions
            State& update(Scene& scene, float deltaTime) noexcept override;

            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_ENEMY_CHASE_H__
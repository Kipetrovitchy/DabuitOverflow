#ifndef __STATE_ENEMY_ATTACK_H__
#define __STATE_ENEMY_ATTACK_H__

#include <vector>
#include "IController.h"
#include "GameObject.h"
#include "StateEnemy.h"

namespace Game::StateMachines
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject     GameObject;
    typedef Resources::Scene            Scene;
    typedef Inputs::InputMgr            InputMgr;
    #pragma endregion

    class StateEnemyAttack : public StateEnemy
    {
        public:
            #pragma region Constructors
            StateEnemyAttack();
            StateEnemyAttack(const StateEnemyAttack& se);
            StateEnemyAttack(Enemy* e);
            StateEnemyAttack(Enemy* e, const std::vector<Transition*>& transitions);
            virtual ~StateEnemyAttack() = default;
            #pragma endregion

            #pragma region Operators
            StateEnemyAttack& operator=(const StateEnemyAttack& se) noexcept;
            #pragma endregion
    
            #pragma region Functions
            State& update(Scene& scene, float deltaTime) noexcept override;

            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_ENEMY_ATTACK_H__
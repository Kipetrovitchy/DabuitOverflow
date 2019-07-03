#ifndef __STATE_ENEMY_IDLE_H__
#define __STATE_ENEMY_IDLE_H__

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

    class StateEnemyIdle : public StateEnemy
    {
        public:
            #pragma region Constructors
            StateEnemyIdle();
            StateEnemyIdle(const StateEnemyIdle& se);
            StateEnemyIdle(Enemy* e);
            StateEnemyIdle(Enemy* e, const std::vector<Transition*>& transitions);
            virtual ~StateEnemyIdle() = default;
            #pragma endregion

            #pragma region Operators
            StateEnemyIdle& operator=(const StateEnemyIdle& se) noexcept;
            #pragma endregion
    
            #pragma region Functions
            State& update(Scene& scene, float deltaTime) noexcept override;

            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_ENEMY_IDLE_H__
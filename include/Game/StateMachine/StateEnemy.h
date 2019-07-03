#ifndef __STATE_ENEMY_H__
#define __STATE_ENEMY_H__

#include <vector>
#include "IController.h"
#include "GameObject.h"
#include "State.h"

namespace Game 
{
    class Enemy;
}
namespace Game::StateMachines
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject GameObject;
    typedef Inputs::InputMgr InputMgr;
    #pragma endregion


    class StateEnemy : public State
    {
        protected:
            #pragma region Attributes
            Enemy*  _enemy;
            #pragma endregion
    
        public:
            #pragma region Constructors
            StateEnemy();
            StateEnemy(const StateEnemy& se);
            StateEnemy(Enemy* e);
            StateEnemy(Enemy* e, const std::vector<Transition*>& transitions);
            virtual ~StateEnemy() = default;
            #pragma endregion

            #pragma region Operators
            StateEnemy& operator=(const StateEnemy& se) noexcept;
            #pragma endregion
    
            #pragma region Functions
            State& init(IController* c) noexcept override final;
            virtual State& update(Scene& scene, float deltaTime) noexcept = 0;

            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_ENEMY_H__
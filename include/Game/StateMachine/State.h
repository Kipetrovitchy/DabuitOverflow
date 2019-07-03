#ifndef __STATE_H__
#define __STATE_H__

#include <vector>
#include "StateMachineObject.h"
#include "IController.h"
#include "Transition.h"
#include "GameObject.h"

namespace Game::StateMachines
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject     GameObject;
    typedef Resources::Scene            Scene;
    typedef ::Game::Inputs::InputMgr    InputMgr;
    #pragma endregion

    class State : public StateMachineObject
    {
        protected:
            #pragma region Attributes
            std::vector<Transition*>     _transitions;
            #pragma endregion
    
        public:
            #pragma region Constructors
            State() = default;
            virtual ~State() = default;
            #pragma endregion
    
            #pragma region Functions
            State&  addTransition(Transition* t) noexcept;
            virtual State& init(IController* c) noexcept = 0;
            virtual State& update(Scene& scene, float deltaTime) noexcept = 0;

            State* checkTransition() noexcept;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__STATE_H__
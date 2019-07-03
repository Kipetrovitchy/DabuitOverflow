#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include <cstdarg>
#include <vector>
#include "StateMachineObject.h"
#include "State.h"
#include "GameObject.h"
#include "Scene.h"

namespace  Game::StateMachines
{
    #pragma region Typedefs
        typedef Resources::Scene    Scene;
    #pragma endregion
    class StateMachine
    {
        protected:
            #pragma region Attributes
                State*                              _currentState; 
                std::vector<StateMachineObject*>    _references;
            #pragma endregion

        public:
            #pragma region Constructors
            StateMachine();
            StateMachine(const StateMachine& sm);
            StateMachine(State* s);
            virtual ~StateMachine();
            #pragma endregion

            #pragma region Operators
            StateMachine& operator=(const StateMachine& sm);
            #pragma endregion

            #pragma region Functions
            virtual StateMachine& update(Scene& scene, float deltaTime) noexcept;
            virtual StateMachine& changeState(State*) noexcept;
            virtual StateMachine& checkTransition() noexcept;

            /**
             *  @brief  Add references to the state machine to prevent leak
             *  @param  size the number of references given
             *  @param  ... pointers to StateMachineObject
             */
            StateMachine& addReferences(size_t size, ...) noexcept;
            #pragma endregion
    };
} // namespace  Game::StateMachine


#endif //__STATE_MACHINE_H__
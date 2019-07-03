#ifndef __DECISION_H__
#define __DECISION_H__

#include "StateMachineObject.h"
#include "IController.h"

namespace Game::StateMachines
{
    class Decision : public StateMachineObject
    {
        protected:
            #pragma region Attributs
            bool _negate;
            #pragma endregion
            
        public:
            #pragma region Constructors
            Decision();
            Decision(const Decision& d);
            Decision(const bool& negate);
            virtual ~Decision() = default;
            #pragma endregion
    
            #pragma region Operators
            Decision& operator=(const Decision& d);
            #pragma endregion

            #pragma region Functions
            virtual Decision*   copy() noexcept = 0;
            virtual Decision&   init(IController*) noexcept = 0;
            virtual bool        isValidated() noexcept = 0;
            #pragma endregion 
    };  
} // namespace Game::StateMachine


#endif //__DECISION_H__
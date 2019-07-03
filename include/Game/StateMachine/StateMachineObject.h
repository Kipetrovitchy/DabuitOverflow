#ifndef __STATE_MACHINE_OBJECT_H__
#define __STATE_MACHINE_OBJECT_H__

namespace Game::StateMachines
{
    class StateMachineObject
    {    
        public:
            #pragma region Constructors
            StateMachineObject() = default;
            virtual ~StateMachineObject() = default;
            #pragma endregion
    };
} // namespace Game::StateMachines

#endif//__STATE_MACHINE_OBJECTS_H__
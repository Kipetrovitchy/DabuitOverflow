#ifndef __IController_H__
#define __IController_H__

namespace Game::StateMachines
{
    
class IController   
{
    public:
        #pragma region Constructors
        IController() = default;
        virtual ~IController() = default;
        #pragma endregion
};

} // namespace Game::StateMachine

#endif //__IController_H__
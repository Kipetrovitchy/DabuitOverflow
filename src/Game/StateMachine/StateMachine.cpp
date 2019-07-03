#include "StateMachine.h"
#include <cstdarg>

namespace Game::StateMachines
{
    StateMachine::StateMachine() :
        _currentState {nullptr}
    {}

    StateMachine::StateMachine(const StateMachine& sm) :
        _currentState {sm._currentState}
    {}

    StateMachine::StateMachine(State* s) : 
        _currentState {s}
    {}

    StateMachine::~StateMachine()
    {
        for (auto it = _references.begin(); it != _references.end();)
        {
            if (*it)
                delete *it;
            
            it = _references.erase(it);
        }
    }

    StateMachine& StateMachine::operator=(const StateMachine& sm)
    {
        _currentState = sm._currentState;

        return *this;
    }

    StateMachine& StateMachine::update(Scene& scene, float deltaTime) noexcept
    {
        if (_currentState)
            _currentState->update(scene, deltaTime);

        checkTransition();

        return *this;
    }

    StateMachine& StateMachine::checkTransition() noexcept
    {
        if (!_currentState)
            return *this;

        State* nextState = _currentState->checkTransition();

        if (nextState)
        {
            changeState(nextState);
        }

        return *this;
    }

    StateMachine& StateMachine::changeState(State* s) noexcept
    {
        _currentState = s;

        return *this;
    }

    StateMachine& StateMachine::addReferences(size_t size, ...) noexcept
    {
        // Get the lists of given arguments
        va_list args;
        va_start(args, size);

        // Go through each given object
        for (uint i = 0; i < size; ++i)
        {
            // Get the current object
            void* pointer = va_arg(args, void*);
            // Check if it exists
            if (pointer)
            {
                // Cast the pointer into a state machine object and add it
                StateMachineObject* smo = static_cast<StateMachineObject*>(pointer);
                _references.push_back(smo);
            }
        }

        va_end(args);

        return *this;
    }   
    // template<typename ... T>
    // void test(typename StateMachineObject<T ...>::type references)
    // {
        
    // }

    // template<typename Arg, typename ... Types>
    // void test(Arg* var, Types* ... references)
    // {
    //     void* values[] = { var, references... };
    //     for (void* v : values )
    //     {
    //         StateMachineObject* smo = dynamic_cast<StateMachineObject*>(v);
    //         if (smo != nullptr)
    //             _pClasses.push_back(smo);
    //     }
    // }

    // template <typename Arg, typename... Ts, typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
    // void test(Arg first, Ts... all) 
    // {
    //     int values[] = { first, all... };
    //     for (auto v : values)
    //     {
    //         std::cout << "msg" << std::endl;
    //     }
    // } 
} // namespace Game::StateMachine  

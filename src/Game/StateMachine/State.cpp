#include "State.h"

namespace Game::StateMachines
{
    #pragma region Fonctions
        State&  State::addTransition(Transition* t) noexcept
        {
            _transitions.push_back(t);

            return *this;
        }

        State* State::checkTransition() noexcept
        {
            for (auto it = _transitions.begin(); it != _transitions.end(); ++it)
            {
                if ((*it)->transition())
                {
                    return (*it)->state();
                }
            }

            return nullptr;
        }
    #pragma endregion
}
 // namespace Game::StateMachines

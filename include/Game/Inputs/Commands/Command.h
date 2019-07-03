#ifndef __COMMAND_H__
#define __COMMAND_H__

namespace Game::Inputs::Commands
{
    class Command
    {
        protected:
        bool _enabled { true };

        public:
            #pragma region Constructors 
            Command() = default;
            virtual ~Command() = default;
            #pragma endregion
    
            #pragma region Functions
            virtual Command& execute() noexcept = 0;
            #pragma endregion

            #pragma region Accessors
            inline bool     enabled() const { return _enabled; }
            inline bool&    enabled()       { return _enabled; }
            #pragma endregion
    };
} // Game::Commands


#endif//__COMMAND_H__
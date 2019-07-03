#include "Log.h"

#include <iostream>
#include <chrono>

namespace Core::Debug
{
    LogPtr Log::s_instance = nullptr;

    Log::Log(Severity severity):
        _severity { severity }
    {}

    Log::~Log()
    {}

    LogPtr Log::getInstance() noexcept
    {
        if (!s_instance)
        {
            #ifdef DEBUG_SEV_DEBUG
                s_instance.reset(new Log(Severity::DEBUG));
            #elif defined(DEBUG_SEV_INFO)
                s_instance.reset(new Log(Severity::INFO));
            #elif defined(DEBUG_SEV_WARNING)
                s_instance.reset(new Log(Severity::WARNING));
            #elif defined(DEBUG_SEV_ERROR)
                s_instance.reset(new Log(Severity::ERROR));
            #else
                s_instance.reset(new Log());
            #endif
        }

        return s_instance;
    }

    void Log::write(Severity severity, const std::string& str) noexcept
    {
        // If the severity is superior to the one used
        if (severity >= _severity)
        {
            // Chose the right way to write
            switch (severity)
            {
                case Severity::DEBUG:     debug(str);     break;
                case Severity::INFO:      info(str);      break;
                case Severity::WARNING:   warning(str);   break;
                case Severity::ERROR:     error(str);     break;
                default: break;
            }
        }

        // If the severity is always write it anyway
        if (severity == Severity::ALWAYS)
            always(str);
    }

    void Log::debug(const std::string& str) noexcept
    {
        // Write the main ligne in cyan bold and underlined
        std::cout << "\e[1;4;36m[Debug] ";
        writeTime();
        std::cout << "\e[0;36m";

        // Write the log
        std::cout << "\t> "  << str;
        std::cout << "\e[0m" << std::endl;
    }

    void Log::info(const std::string& str) noexcept
    {
        // Write the main ligne in yellow bold and underlined
        std::cout << "\e[1;4;33m[Info] ";
        writeTime();
        std::cout << "\e[0;33m";

        // Write the log
        std::cout << "\t> "  << str;
        std::cout << "\e[0m" << std::endl;
    }

    void Log::warning(const std::string& str) noexcept
    {
        // Write the main ligne in magenta bold and underlined
        std::cout << "\e[1;4;35m[Warning] ";
        writeTime();
        std::cout << "\e[0;35m";

        // Write the log
        std::cout << "\t> "  << str;
        std::cout << "\e[0m" << std::endl;
    }

    void Log::error(const std::string& str) noexcept
    {
        // Write the main ligne in red bold and underlined
        std::cout << "\e[1;4;31m[Error] ";
        writeTime();
        std::cout << "\e[0;31m";

        // Write the log
        std::cout << "\t> "  << str;
        std::cout << "\e[0m" << std::endl;
    }

    void Log::always(const std::string& str) noexcept
    {
        // Write the main ligne in white bold and underlined
        std::cout << "\e[1;4;37m[Always] ";
        writeTime();
        std::cout << "\e[0;37m";

        // Write the log
        std::cout << "\t> "  << str;
        std::cout << "\e[0m" << std::endl;
    }

    void Log::writeTime() noexcept
    {
        std::time_t t = std::time(0);
        std::tm* now  = std::localtime(&t);
        std::cout << now->tm_hour << "h:" << now->tm_min << "m:" << now->tm_sec;
    }
} /* Debug */

#include "Assert.h"
#include <iostream>

namespace Core::Debug
{
    void assert(const char* file, int line, bool condition) noexcept
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[0m" << std::endl;
        }
    }

    void assert(const char* file, int line, bool condition,
                const std::string& msg) noexcept
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[22m : "                << msg
                      << "\e[0m" << std::endl;
        }
    }

    void assert(const char* file, int line, bool condition, const std::string& msg,
                const std::string& detail) noexcept
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[22m : "                << msg
                      << std::endl                  << "\t\e[36m>\e[0m"
                      << detail                     << std::endl;
        }
    }

    bool assertOut(const char* file, int line, bool condition) noexcept
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[0m" << std::endl;
        }

        return condition;
    }

    bool assertOut(const char* file, int line, bool condition,
                   const std::string& msg) noexcept
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[22m : "                << msg
                      << "\e[0m" << std::endl;
        }

        return condition;
    }

    bool assertOut(const char* file, int line, bool condition,
                   const std::string& msg, const std::string& detail) noexcept
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[22m : "                << msg
                      << "\e[0m"                    << std::endl
                      << detail                     << std::endl;
        }

        return condition;
    }

    void assertThrow(const char* file, int line, bool condition)
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[0m" << std::endl;

            throw std::string();
        }
    }

    void assertThrow(const char* file, int line, bool condition, const std::string& msg)
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[22m : "                << msg
                      << "\e[0m" << std::endl;

            throw std::string();
        }
    }

    void assertThrow(const char* file, int line, bool condition, const std::string& msg,
                const std::string& detail)
    {
        if (!condition)
        {
            std::cout << "\e[31mAssertion in \e[1m" << file
                      << "\e[22m at line \e[1m"     << line
                      << "\e[22m : "                << msg
                      << "\e[0m"                    << std::endl
                      << detail                     << std::endl;

            throw std::string();
        }
    }
} /* Core::Debug */

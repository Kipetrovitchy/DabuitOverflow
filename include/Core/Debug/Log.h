#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <memory>

//#define NDEBUG

#define DEBUG_SEV_INFO

namespace Core::Debug
{
    class Log;
    typedef std::shared_ptr<Log> LogPtr;

    // Log is a singleton class
    class Log
    {
    public:
        enum class Severity
        {
            DEBUG = 0,
            INFO,
            WARNING,
            ERROR,
            ALWAYS
        };

    private:
        Severity _severity;

        static LogPtr s_instance;

        Log(Severity severity = Severity::ERROR);

    public:

        ~Log();

        static LogPtr getInstance() noexcept;

        void write  (Severity severity, const std::string& msg) noexcept;

        void debug  (const std::string& msg) noexcept;
        void info   (const std::string& msg) noexcept;
        void warning(const std::string& msg) noexcept;
        void error  (const std::string& msg) noexcept;
        void always (const std::string& msg) noexcept;

        void writeTime() noexcept;

    };
} /* Debug */

#ifndef DEF_LOG
    #define DEF_LOG
    #ifdef NDEBUG
        // If the macro variable NDEBUG is defined then disable the LOG macro
        #define LOG(sev, msg) (void)0
    #else
        // Define the macro to use the log
        #define LOG(sev, msg) \
            Core::Debug::Log::getInstance()->write(Core::Debug::Log::Severity::sev, msg)
    #endif
#endif

#endif//__LOH_H__

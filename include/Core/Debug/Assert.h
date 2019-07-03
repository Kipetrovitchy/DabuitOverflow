#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <string>

//#define NDEBUG

namespace Core::Debug
{
    // Basic assertions
    void assert(const char* file, int line, bool condition)           noexcept;
    void assert(const char* file, int line, bool condition,
                const std::string& msg)                               noexcept;
    void assert(const char* file, int line, bool condition,
                const std::string& msg, const std::string& detail)    noexcept;
    // Assertions that return the value of the boolean
    bool assertOut(const char* file, int line, bool condition)        noexcept;
    bool assertOut(const char* file, int line, bool condition,
                   const std::string& msg)                            noexcept;
    bool assertOut(const char* file, int line, bool condition,
                   const std::string& msg, const std::string& detail) noexcept;
    // Assetions that throws errors
    void assertThrow(const char* file, int line, bool condition);
    void assertThrow(const char* file, int line, bool condition,
                     const std::string& msg);
    void assertThrow(const char* file, int line, bool condition,
                     const std::string& msg, const std::string& detail);
} /* Debug */

#ifndef DEF_ASSERT
    #define DEF_ASSERT
    #define TO_BOOL(boolean) (boolean) ? true : false
    #ifdef NDEBUG
        // Disable the assertion if the macro NDEBUG is defined
        #define ASSERT(cond) (void)0
        #define ASSERT_MSG(cond, msg) (void)0
        #define ASSERT_DET(cond, msg, det) (void)0

        #define ASSERT_OUT(cond) cond
        #define ASSERT_OUT_MSG(cond, msg) cond
        #define ASSERT_OUT_DET(cond, msg, det) cond

        #define ASSERT_THROW(cond) if (!cond) throw std::string()
        #define ASSERT_THROW_MSG(cond, msg) if (!cond) throw std::string()
        #define ASSERT_THROW_DET(cond, msg, det) if (!cond) throw std::string()
    #else
        // Define the variable to write the file and the line
        #define FL __FILE__, __LINE__

        // Create the macros to use the assertion
        #define ASSERT(cond) \
            Core::Debug::assert(FL, TO_BOOL(cond))
        #define ASSERT_MSG(cond, msg) \
            Core::Debug::assert(FL, TO_BOOL(cond), msg)
        #define ASSERT_DET(cond, msg, det) \
            Core::Debug::assert(FL, TO_BOOL(cond), msg, det)

        // Assertion macros that returns the value of the assertion
        #define ASSERT_OUT(cond) \
            Core::Debug::assertOut(FL, TO_BOOL(cond))
        #define ASSERT_OUT_MSG(cond, msg) \
            Core::Debug::assertOut(FL, TO_BOOL(cond), msg)
        #define ASSERT_OUT_DET(cond, msg, det) \
            Core::Debug::assertOut(FL, TO_BOOL(cond), msg, det)

        // Assertion macros that throws an error
        #define ASSERT_THROW(cond) \
            Core::Debug::assertThrow(FL, TO_BOOL(cond))
        #define ASSERT_THROW_MSG(cond, msg) \
            Core::Debug::assertThrow(FL, TO_BOOL(cond), msg)
        #define ASSERT_THROW_DET(cond, msg, det) \
            Core::Debug::assertThrow(FL, TO_BOOL(cond), msg, det)
    #endif
#endif

#endif//__ASSERT_H__

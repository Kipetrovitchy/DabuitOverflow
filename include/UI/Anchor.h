#ifndef __ANCHOR_H__
#define __ANCHOR_H__

#include <GL/glew.h>

#define BIT_CENTER  0x01
#define BIT_RIGHT   0x02
#define BIT_LEFT    0x04
#define BIT_BOT     0x08
#define BIT_MID     0x10
#define BIT_TOP     0x20

namespace UI
{
    enum class EAnchor : GLuint
    {
        TOPLEFT     = BIT_TOP | BIT_LEFT,
        TOPCENTER   = BIT_TOP | BIT_CENTER,
        TOPRIGHT    = BIT_TOP | BIT_RIGHT,
        MIDLEFT     = BIT_MID | BIT_LEFT,
        MIDCENTER   = BIT_MID | BIT_CENTER,
        MIDRIGHT    = BIT_MID | BIT_RIGHT,
        BOTLEFT     = BIT_BOT | BIT_LEFT,
        BOTCENTER   = BIT_BOT | BIT_CENTER,
        BOTRIGHT    = BIT_BOT | BIT_RIGHT
    };

    class Anchor
    {
        private:
            #pragma region Attributes
            GLuint _anchor :6;
            #pragma endregion

        public:
            #pragma region Constructors / Destructors
            Anchor();
            Anchor(const Anchor& a);
            Anchor(const GLuint anchor);
            Anchor(const EAnchor anchor);
            ~Anchor() = default;
            #pragma endregion

            #pragma region Operators
            Anchor& operator=(const Anchor& a);
            Anchor& operator=(const EAnchor& a);
            #pragma endregion

            #pragma region Accessors
            inline GLuint getValue() const { return _anchor; }
            inline EAnchor getEnum() const { return static_cast<EAnchor>(_anchor); }

            Anchor& setAnchor(GLuint value);
            Anchor& setAnchor(EAnchor value);
            #pragma endregion
    };
    
} // namespace UI

#endif //_ANCHOR_H__
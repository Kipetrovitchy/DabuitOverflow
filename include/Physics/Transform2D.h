#ifndef __TRANSFORM2D_H__
#define __TRANSFORM2D_H__

#include "LibMaths.h"
#include "Anchor.h"
#include <GL/glew.h>

namespace Physics
{
    #pragma region typedefs
    typedef Core::Maths::Vec3   Vec3;
    typedef Core::Maths::Mat    Mat;
    typedef UI::Anchor          Anchor;
    #pragma endregion
    class Transform2D
    {
        private:
            #pragma region Attributes
            Vec3 _anchoredPos;
            Vec3 _position;
            Vec3 _rotation;

            GLuint _width;
            GLuint _height;

            Anchor _anchor;
            Mat    _trs;
            Transform2D* _parent;
            #pragma endregion
            #pragma region Private Methods
            Transform2D& updateTRS()        noexcept;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Transform2D()                                                   noexcept;
            Transform2D(const Transform2D& t)                               noexcept;
            Transform2D(const Vec3& pos)                                    noexcept;
            Transform2D(const Vec3& pos, const Vec3& rot, const GLuint width, 
                        const GLuint height, const Anchor& anchor)          noexcept;
            ~Transform2D() = default;
            #pragma endregion
    
            #pragma region Operators
            Transform2D& operator=(const Transform2D& t) noexcept;
            #pragma endregion
    
            #pragma region Methods
            Transform2D& setAnchoredPosition(const Vec3& pos)   noexcept;
            Transform2D& setRotation(const Vec3& rot)           noexcept;
            Transform2D& setWidth(const GLuint width)           noexcept;
            Transform2D& setHeight(const GLuint height)         noexcept;
            Transform2D& setAnchor(const UI::EAnchor anchor)    noexcept;
            Transform2D& setParent(Transform2D* parent)         noexcept;

            Transform2D& updatePosition()                       noexcept;
            #pragma endregion

            #pragma region Accessors
            inline Vec3     anchoredPos() const { return _anchoredPos; }
            inline Vec3     position() const { return _position; }

            inline Vec3     rotation() const { return _rotation; }

            inline GLuint   width() const { return _width; }

            inline GLuint   height() const { return _height; }

            inline Mat      TRS() const { return _trs; }
            #pragma endregion
    };
} // namespace Physics

#endif // __TRANSFORM2D_H__
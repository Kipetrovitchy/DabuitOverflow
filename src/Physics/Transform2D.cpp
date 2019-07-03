#include "Transform2D.h"
#include "Canvas.h"
#include "Transform.h"

namespace Physics
{
    
    #pragma region Constructors / Destructors
    Transform2D::Transform2D() noexcept : 
        _anchoredPos { Vec3::zero},
        _position { Vec3::zero },
        _rotation { Vec3::zero },
        _width { 100 },
        _height { 50 },
        _trs { Mat::identity(4) },
        _parent { &Resources::Canvas::windowTransform() }
    {}
    Transform2D::Transform2D(const Transform2D& t) noexcept :
        _anchoredPos { t._anchoredPos },
        _position { t._position },
        _rotation { t._rotation },
        _width { t._width },
        _height { t._height },
        _anchor { t._anchor },
        _trs { t._trs },
        _parent { t._parent }
    {}

    Transform2D::Transform2D(const Vec3& pos) noexcept :
        _position { pos }
    {
        updateTRS();
    }

    Transform2D::Transform2D(const Vec3& pos, const Vec3& rot, const GLuint width, 
                             const GLuint height, const Anchor& anchor) noexcept :
        _anchoredPos { pos },
        _rotation { rot },
        _width { width },
        _height { height },
        _anchor { anchor },
        _parent { &Resources::Canvas::windowTransform() }
    {
        updateTRS();
    }
    #pragma endregion

    #pragma region Operators
    Transform2D& Transform2D::operator=(const Transform2D& t) noexcept
    {
        _anchoredPos = t._anchoredPos;
        _position = t._position;
        _rotation = t._rotation;
        _width = t._width;
        _height = t._height;
        _anchor = t._anchor;
        _trs = t._trs;
        _parent = t._parent;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    Transform2D& Transform2D::setAnchoredPosition(const Vec3& pos) noexcept
    {
        _anchoredPos = pos;

        updatePosition();
        return *this;
    }


    Transform2D& Transform2D::setRotation(const Vec3& rot) noexcept
    {
        _rotation = rot;

        updateTRS();
        return *this;
    }

    Transform2D& Transform2D::setWidth(const GLuint width)   noexcept
    {
        _width = width;

        updatePosition();
        return *this;
    }

    Transform2D& Transform2D::setHeight(const GLuint height) noexcept
    {
        _height = height;

        updatePosition();
        return *this;
    }

    Transform2D& Transform2D::setAnchor(const UI::EAnchor anchor) noexcept
    {
        _anchor = anchor;

        updatePosition();
        return *this;
    }

    Transform2D& Transform2D::setParent(Transform2D* parent) noexcept
    {
        _parent = parent;

        updatePosition();
        return *this;
    }

    Transform2D& Transform2D::updatePosition() noexcept
    {
        _position = _anchoredPos;
        GLuint anchorValue { _anchor.getValue() };

        //Update the anchored position based on the y placement
        if (anchorValue & BIT_TOP)
            _position.y += _parent->height() / 2.f;
        else if (anchorValue & BIT_BOT)
            _position.y -= _parent->height() / 2.f;

        //Update the anchored position based on the x placement
        if (anchorValue & BIT_LEFT)
            _position.x -= _parent->width() / 2.f;
        else if (anchorValue & BIT_RIGHT)
            _position.x += _parent->width() / 2.f;

        updateTRS();
        return *this;
    }

    #pragma endregion

    #pragma region Private Methods
    Transform2D& Transform2D::updateTRS() noexcept
    {
        _trs = Physics::Transform::createTransformMatrix(_rotation,
                                                         _position,
                                                         Vec3::one);

        return *this;
    }
    #pragma endregion
} // namespace Physics

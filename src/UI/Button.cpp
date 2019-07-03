#include "Button.h"
#include "Transform.h"
#include "3DCollisions.h"
#include "Canvas.h"

namespace UI
{
    #pragma region Constructors / Destructors
    Button::Button() : 
        BaseUIComponent(),
        _image { new Image() },
        _text { new Text() },
        _pointerDownIn { false },
        _updateDisabled { false },
        _baseColor { 1.f, 1.f, 1.f, 1.f },
        _hoverColor { 0.8f, 0.8f, 0.8f, 1.f },
        _clickColor { 0.6f, 0.6f, 0.6f, 1.f },
        _disableColor { 0.3f, 0.3f, 0.3f, 1.f }

    {
        addChild(_image);
        addChild(_text);
        _targetsColor.push_back(_image);
    }

    Button::Button(const Button& b) :
        BaseUIComponent(),
        _pointerDownIn { b._pointerDownIn },
        _updateDisabled {b._updateDisabled },
        _baseColor { b._baseColor },
        _hoverColor { b._hoverColor },
        _clickColor { b._clickColor },
        _disableColor { b._disableColor },
        _onClick { b._onClick }
    {
        _transform = b._transform;
        //Duplicate all the children and retrieve the image and text of button
         for (auto it = b._children.begin(); it != b._children.end(); ++it)
        {
            if ((*it) == b._image)
            {
                _image = new Image(*b._image);
                addChild(_image);
            }

            if ((*it) == b._text)
            {
                _text = new Text(*b._text);
                addChild(_text);
            }

            if (*it)
                addChild(new BaseUIComponent(*(*it)));
        }

        /*for (auto it = b._onClick.begin(); it != b._onClick.end(); ++it)
            if (*it)
                _onClick.push_back(new std::function<void()>(**it));*/
    }

    Button::Button(Resources::Texture* texture, Resources::Shader* imgShader,
                   Resources::Font* font, Resources::Shader* textShader) : 
        BaseUIComponent(),
        _pointerDownIn { false },
        _updateDisabled { false },
        _baseColor { 1.f, 1.f, 1.f, 1.f },
        _hoverColor { 0.8f, 0.8f, 0.8f, 1.f },
        _clickColor { 0.6f, 0.6f, 0.6f, 1.f },
        _disableColor { 0.3f, 0.3f, 0.3f, 1.f }
    {
        init(texture, imgShader, font, textShader);
    }

    Button::~Button()
    {
        /*for (auto it = _onClick.begin(); it != _onClick.end(); ++it)
            if (*it)
                delete (*it);*/
    }
    #pragma endregion

    #pragma region Operators
    Button& Button::operator=(const Button& b) noexcept
    {
        _pointerDownIn = b._pointerDownIn;
        _onClick.clear();
        _onClick = b._onClick;
        _transform = b._transform;

        for (auto it = b._children.begin(); it != b._children.end(); ++it)
        {
            if ((*it) == b._image)
            {
                _image = new Image(*b._image);
                addChild(_image);
                continue;
            }

            if ((*it) == b._text)
            {
                _text = new Text(*b._text);
                addChild(_text);
                continue;
            }

            if (*it)
                addChild(new BaseUIComponent(*(*it)));
        }

        /*for (auto it = b._onClick.begin(); it != b._onClick.end(); ++it)
            if (*it)
                _onClick.push_back(new std::function<void()>(**it));*/

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    Button& Button::init(Resources::Texture* texture, Resources::Shader* imgShader,
                         Resources::Font* font, Resources::Shader* textShader) noexcept
    {
        _image = new Image(texture, imgShader);
        _text = new Text(font, textShader);
        
        _image->transform().setAnchoredPosition({0, 0, -.9f});
        _text->transform().setAnchoredPosition({0, 0, -1.f});
        addChild(_text);
        addChild(_image);
        _targetsColor.push_back(_image);

        return *this;
    }

    Button& Button::addListener(std::function<void()> func) noexcept
    {
        _onClick.emplace_back(func);
        return *this;
    }

    Button& Button::clearListeners() noexcept
    {
        _onClick.clear();

        return *this;
    }

    BaseUIComponent& Button::update(Mat transformParent, const InputModule& module) noexcept
    {
        //We don't update the button if it's disabled
        if (!_enabled || _updateDisabled)
            return *this;
        
        transformParent = transformParent * _transform.TRS();
        //Create the hitbox
        Quad area;
        createArea(transformParent, area);

        //Create a raycast with the mouse position and the hitbox
        Core::Maths::Segment mouseSeg { Vec3{ module.mousePos(),  100 },
                                        Vec3{ module.mousePos(), -100 } };
        Physics::Collisions::SegmentHit* hit;
        bool isMouseOver { Physics::Collisions::segmentQuad(mouseSeg, area, hit) };
        
        //Delete the hit informations, we don't use it
        if (isMouseOver)
        {
            updateTargetsColor(_hoverColor);
            delete hit;
        }

        //Update the boolean if the mouse clicked on the button
        if (isMouseOver && module.submit())
        {
            updateTargetsColor(_clickColor);
            _pointerDownIn = true;
        }
        //Click released on the button, we activate all the functions of onClick
        else if (isMouseOver && !module.submit() && _pointerDownIn)
        {
            _pointerDownIn = false;
            updateTargetsColor(_baseColor);
            invokeOnClick();
        }
        //Click released not on the button, nothing happens
        else if (!isMouseOver && !module.submit())
        {
            updateTargetsColor(_baseColor);
            _pointerDownIn = false;
        }

        updateChildren(transformParent, module);

        return *this;
    }
    
    #pragma region Accessors
    BaseUIComponent& Button::setWidth(GLuint width)     noexcept
    {
        _transform.setWidth(width);
        _image->setWidth(width);
        _text->setWidth(width);

        return *this;
    }

    BaseUIComponent& Button::setHeight(GLuint height)   noexcept
    {
        _transform.setHeight(height);
        _image->setHeight(height);
        _text->setHeight(height);
        
        return *this;
    }

    Button& Button::disableUpdate(bool state) noexcept
    {
        _updateDisabled = state;
        if (_updateDisabled)
            updateTargetsColor(_disableColor);

        return *this;
    }
    #pragma endregion

    #pragma region Private Functions
    void Button::createArea(const Mat& transform, Quad& area) noexcept
    {
        //Place the hitbox. Tweak with the y value because the mouse position is 0,0
        //in bot left and the ui component's position are in 0,0 for topleft;
        area.origin.o = transform * Vec3::zero;
        area.origin.o.y += Resources::Canvas::windowTransform().height() / 2.f;

        //Create the rotation matrix for the quad axis
        Mat rot = Physics::Transform::createEulerRotation(_transform.rotation());

        area.origin.i = rot * Vec3::right;
        area.origin.j = rot * Vec3::forward;
        area.origin.k = rot * Vec3::down;

        area.hWidth = _transform.width() / 2.f;
        area.hHeight = _transform.height() / 2.f;
    }

    void Button::invokeOnClick() noexcept
    {
        for (auto it = _onClick.begin(); it != _onClick.end(); ++it)
        {
            if (*it)
                (*it)();
        }
    }

    void Button::updateTargetsColor(Vec4 color) noexcept
    {
        for (auto it = _targetsColor.begin(); it != _targetsColor.end(); ++it)
        {
            if (*it)
                (*it)->color() = color;
        }
    }
    #pragma endregion
} // namespace UI

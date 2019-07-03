#include "BaseUIComponent.h"

namespace UI
{
    #pragma region Constructors / Destructors
    BaseUIComponent::BaseUIComponent() noexcept :
        _enabled { true }
    {}
    
    BaseUIComponent::BaseUIComponent(const BaseUIComponent& bc) noexcept :
        _transform { bc._transform }
    {
        for (auto it = bc._children.begin(); it != bc._children.end(); ++it)
        {
            if (*it)
                addChild(new BaseUIComponent(*(*it)));
        }
    }

    BaseUIComponent::~BaseUIComponent() noexcept
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
            if (*it)
                delete *it;
    }
    #pragma endregion

    #pragma region Operators
    BaseUIComponent& BaseUIComponent::operator=(const BaseUIComponent& bc) noexcept
    {
        _transform = bc._transform;

        for (auto it = bc._children.begin(); it != bc._children.end(); ++it)
        {
            if (*it)
                addChild(new BaseUIComponent(*(*it)));
        }

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    BaseUIComponent& BaseUIComponent::setActive(bool state) noexcept
    {
        _enabled = state;
        for (auto it = _children.begin(); it != _children.end(); ++it)
            (*it)->setActive(state);

        return *this;
    }

    BaseUIComponent* BaseUIComponent::addChild(BaseUIComponent* child) noexcept
    {
        child->transform().setParent(&_transform);
        _children.push_back(child);

        return child;
    }

    BaseUIComponent& BaseUIComponent::update(Mat transformParent,
                                             const InputModule& module) noexcept
    {
        transformParent = transformParent * _transform.TRS();
        
        updateChildren(transformParent, module);

        return *this;
    }

    BaseUIComponent& BaseUIComponent::render(Mat transformParent) noexcept
    {
        //We don't render the object and its children if it is disabled
        if (!_enabled)
            return *this;

        transformParent = transformParent * _transform.TRS();
        
        renderChildren(transformParent);

        return *this;
    }
    #pragma endregion

    #pragma region Accessors
    BaseUIComponent& BaseUIComponent::setWidth(GLuint width) noexcept
    {
        _transform.setWidth(width);
        updateChildrenTransform();
        
        return *this;
    }

    BaseUIComponent& BaseUIComponent::setHeight(GLuint height) noexcept
    {
        _transform.setHeight(height);
        updateChildrenTransform();

        return *this;
    }
    #pragma endregion

    #pragma region Private Methods
    BaseUIComponent& BaseUIComponent::updateChildrenTransform() noexcept
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->transform().updatePosition();
        }

        return *this;
    }

    BaseUIComponent& BaseUIComponent::renderChildren(const Mat& transform) noexcept
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            if (*it)
            {
                (*it)->render(transform);
            }
        }

        return *this;
    }

    BaseUIComponent& BaseUIComponent::updateChildren(const Mat& transform,
                                                     const InputModule& module) noexcept
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            if (*it)
            {
                (*it)->update(transform, module);
            }
        }

        return *this;
    }
    #pragma endregion
} // namespace UI

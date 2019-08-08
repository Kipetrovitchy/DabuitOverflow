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

    BaseUIComponent& BaseUIComponent::render(Mat viewProj) noexcept
    {
        //We don't render the object and its children if it is disabled
        if (!_enabled)
            return *this;

        (void)viewProj;

        return *this;
    }
    BaseUIComponent& BaseUIComponent::sortPreRender(Vec3 camPos, Vec3 parentPos, 
    std::list<BaseUIComponent*>& opaques, std::multimap<float, BaseUIComponent*>& translucents) noexcept
    {
        if (!_enabled)
            return *this;

        Vec3 globalPos { globalPosition(parentPos) };

        if (_isOpaque)
            opaques.push_back(this);
        else
            translucents.emplace((globalPos - camPos).length(), this);

        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            if (*it)
                (*it)->sortPreRender(camPos, globalPos, opaques, translucents);
        }

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

    Vec3 BaseUIComponent::globalPosition(Vec3 parentPos)
    {
        return _transform.position() + parentPos;
    }
    #pragma endregion
} // namespace UI

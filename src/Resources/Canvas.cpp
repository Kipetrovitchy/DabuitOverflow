#include "Canvas.h"
#include "Window.h"
#include "Transform2D.h"


namespace Resources
{
    Physics::Transform2D	Canvas::s_windowTransform;

    #pragma region Constructors / Desctructors
    Canvas::Canvas(const Canvas& c) noexcept
    {
        for (auto it = c._children.begin(); it != c._children.end(); ++it)
        {
            if (*it)
                addChild(new BaseUIComponent(*(*it)));
        }
    }

    Canvas::~Canvas()
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
            if (*it)
                delete *it;
    }
    #pragma endregion
    
    #pragma region Operators
    Canvas& Canvas::operator=(const Canvas& c) noexcept
    {
        _children.clear();
        
        for (auto it = c._children.begin(); it != c._children.end(); ++it)
        {
            if (*it)
                addChild(new BaseUIComponent(*(*it)));
        }
        return *this;
    }
    #pragma endregion

    #pragma region Methods
    BaseUIComponent* Canvas::addChild(BaseUIComponent* child) noexcept
    {
        child->transform().setParent(&s_windowTransform);
        _children.push_back(child);

        return child;
    }

    Canvas& Canvas::update(const InputModule& module)
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            if (*it)
                (*it)->update(Mat::identity(4), module);
        }

        return *this;
    }

    Canvas& Canvas::render(const Mat& viewProj, Vec3 camPos) noexcept
    {
        std::list<BaseUIComponent*> opaques;
        std::multimap<float, BaseUIComponent*> translucents;
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            if (*it)
                (*it)->sortPreRender(camPos, {0, 0, 0}, opaques, translucents);
        }

        for (auto it { opaques.begin() }; it != opaques.end(); ++it)
        {
            if (*it)
                (*it)->render(viewProj);
        }

        for (auto it {translucents.rbegin()}; it != translucents.rend(); ++it)
        {
            if (it->second)
                (it->second)->render(viewProj);
        }

        return *this;
    }

    Canvas& Canvas::updateChildrenTransform() noexcept
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->transform().updatePosition();
        }

        return *this;
    }
    #pragma endregion
} // namespace Resources

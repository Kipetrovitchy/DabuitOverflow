#ifndef __BASE_UI_COMPONENT_H__
#define __BASE_UI_COMPONENT_H__

#include "Vec3.h"
#include "Transform2D.h"
#include "Anchor.h"
#include "Mat.h"
#include "InputModule.h"

#include <vector>
#include <list>
#include <map>

namespace UI
{

    #pragma region Typedefs
    typedef Core::Maths::Vec3   Vec3;
    typedef Core::Maths::Mat    Mat; 
    typedef Physics::Transform2D Transform2D;
    typedef Game::Inputs::InputModule InputModule;
    #pragma endregion

    class BaseUIComponent
    {
        protected:
            #pragma region Attributes
            //dirty bool here to test the transparency support
            bool _isOpaque { true };
            bool _enabled;
            Transform2D _transform;

            std::vector<BaseUIComponent*> _children;
            #pragma endregion

            #pragma region Private Methods
            BaseUIComponent& updateChildrenTransform()              noexcept;
            BaseUIComponent& updateChildren(const Mat& transform,
                                            const InputModule& module) noexcept;
            
            Vec3 globalPosition(Vec3 parentPos);
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            BaseUIComponent()                           noexcept;
            BaseUIComponent(const BaseUIComponent& bc)  noexcept;
            virtual ~BaseUIComponent()                  noexcept;
            #pragma endregion
    
            #pragma region Operators
            BaseUIComponent& operator=(const BaseUIComponent& bc) noexcept;
            #pragma endregion
    
            #pragma region Methods
            BaseUIComponent& setActive(bool state)  noexcept;
            BaseUIComponent* addChild(BaseUIComponent* child)    noexcept;
            virtual BaseUIComponent& update(Mat transformParent,
                                            const InputModule& module) noexcept;
            virtual BaseUIComponent& render(Mat viewProj) noexcept;
            BaseUIComponent& sortPreRender(Vec3 camPos, Vec3 parentPos, 
                                           std::list<BaseUIComponent*>& opaques,
                                           std::multimap<float, BaseUIComponent*>& translucents) noexcept;
            #pragma endregion

            #pragma region Accessors
            inline Transform2D     transform() const { return _transform; }
            inline Transform2D&    transform()       { return _transform; }
            inline bool            enabled()   const { return _enabled; }
            inline bool&           isOpaque()        { return _isOpaque; }

            virtual BaseUIComponent& setWidth(GLuint width)     noexcept;
            virtual BaseUIComponent& setHeight(GLuint height)   noexcept;
            #pragma endregion
    };
} // namespace UI

#endif // __BASE_UI_COMPONENT_H__
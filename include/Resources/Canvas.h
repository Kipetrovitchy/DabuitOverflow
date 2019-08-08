#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "BaseUIComponent.h"
#include "Mat.h"
#include "InputModule.h"

namespace Physics
{
    class Transform2D;
} // namespace Physics

namespace Resources
{
    #pragma region typedefs
    typedef UI::BaseUIComponent         BaseUIComponent;
    typedef Core::Maths::Mat            Mat;
    typedef Core::Maths::Vec3           Vec3;
    typedef Physics::Transform2D        Transform2D;
    typedef Game::Inputs::InputModule   InputModule;
    #pragma endregion

    class Canvas
    {
        private:
            #pragma region Attributes
            std::vector<BaseUIComponent*>  _children;
            #pragma endregion

            #pragma region Private Methods
            #pragma endregion
            //Root of hierarchy for UI elements
            static Transform2D s_windowTransform;
        public:
            #pragma region Constructors / Destructors
            Canvas() = default;
            Canvas(const Canvas& c) noexcept;
            ~Canvas()               noexcept;
            #pragma endregion
    
            #pragma region Operators
            Canvas& operator=(const Canvas& c) noexcept;
            #pragma endregion
    
            #pragma region Methods
            BaseUIComponent* addChild(BaseUIComponent* child) noexcept;

            Canvas& update(const InputModule& module);
            Canvas& render(const Mat& viewProj, Vec3 camPos) noexcept;
            Canvas& updateChildrenTransform() noexcept;
            #pragma endregion

            #pragma region Accessors
            inline std::vector<BaseUIComponent*> children() const { return _children; }
            #pragma endregion

            static inline Transform2D* windowTransform() { return &s_windowTransform; }
    };
} // namespace Resources

#endif // __CANVAS_H__
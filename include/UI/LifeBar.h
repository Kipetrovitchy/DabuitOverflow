#ifndef __LIFE_BAR_H__
#define __LIFE_BAR_H__

#include "Image.h"
#include "Canvas.h"
#include "ResourcesManager.h"

namespace UI
{
    #pragma region Typedefs
    typedef Resources::ResourcesManager ResourcesManager;
    typedef Resources::Canvas           Canvas;
    #pragma endregion
    class LifeBar
    {
        private:
            #pragma region Attributes
            Image* _fg;
            Image* _bg;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            LifeBar()                       noexcept;
            LifeBar(const LifeBar& lifebar) noexcept;
            LifeBar(ResourcesManager* mgr, Canvas* hud) noexcept;
            ~LifeBar() = default;
            #pragma endregion
    
            #pragma region Operators
            LifeBar& operator=(const LifeBar& lifebar) noexcept;
            #pragma endregion
    
            #pragma region Methods
            LifeBar& init(ResourcesManager* mgr, Canvas* hud);
            LifeBar& updateHP(int actual, int max);
            #pragma endregion
    };
} // namespace UI

#endif // __LIFE_BAR_H__
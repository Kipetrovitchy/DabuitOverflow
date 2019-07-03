#ifndef __JOHAN_H__
#define __JOHAN_H__

#include "Text.h"
#include "ResourcesManager.h"
#include "Canvas.h"

namespace UI
{
    #pragma region typedefs
    typedef Resources::ResourcesManager ResourcesManager;
    typedef Resources::Canvas Canvas;
    #pragma endregion
    class Johan
    {
        private:
            #pragma region Attributes
            Text* _flo;
            Text* _sam;
            Text* _paul;
            Text* _etienne;

            Text* _insaneProducerGroup;

            Text* _ty;

            float _rotation;
            bool  _enabled;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Johan() noexcept;
            Johan(const Johan& j) = delete;
            ~Johan() = default;
            #pragma endregion
    
            #pragma region Methods
            Johan& init(ResourcesManager* mgr, Canvas* mainMenu) noexcept;
            Johan& update(float deltatime)             noexcept;
            Johan& setActive()                                   noexcept;
            #pragma endregion
    };
} // namespace UI

#endif // __JOHAN_H__
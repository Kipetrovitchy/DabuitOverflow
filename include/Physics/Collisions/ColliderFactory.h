#ifndef __COLLIDER_FACTORY_H__
#define __COLLIDER_FACTORY_H__

#include "Collider.h"

namespace Physics::Collisions
{
    enum EColliderType
    {
        BOX,
        SPHERE,
        COUNT
    };

    Collider* createColliderOfType(const EColliderType& type,
                                   GameObject* gO = nullptr,
                                   bool isTrigger = false) noexcept;
}

#endif//__COLLIDER_TYPE_H__
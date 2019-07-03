#include "ColliderFactory.h"

#include "BoxCollider.h"
#include "SphereCollider.h"

namespace Physics::Collisions
{
    Collider* createColliderOfType(const EColliderType& type,
                                   GameObject* gO,
                                   bool isTrigger) noexcept
    {
        switch (type)
        {
            case EColliderType::BOX: return new BoxCollider(gO, isTrigger);
            case EColliderType::SPHERE: return new SphereCollider(gO, isTrigger);
            default: return nullptr;
        }
    }
} // Physics::Collisions

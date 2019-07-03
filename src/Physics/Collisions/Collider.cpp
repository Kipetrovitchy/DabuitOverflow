#include "Collider.h"
#include "GameObject.h"

namespace Physics::Collisions
{
    Collider::Collider():
        _gameObject     { nullptr },
        _isTrigger      { false }
    {}

    Collider::Collider(GameObject* gO, bool isTrigger):
        _gameObject     { gO },
        _isTrigger      { isTrigger }
    {}
    
    Collider::Collider(const Collider& c):
        _gameObject      { c._gameObject },
        _isTrigger       { c._isTrigger }
    {}

    Collider& Collider::operator=(const Collider& c)
    {
        _gameObject = c._gameObject;
        _isTrigger  = c._isTrigger;

        return *this;
    }

    Collider& Collider::onCollision(Scene& scene, Collider* collider, SegmentHit* hit) noexcept
    {
        if (_gameObject)
        {
            if (_isTrigger)
                _gameObject->onTrigger(scene, collider, hit);
            else
                _gameObject->onCollision(scene, collider, hit);
        }
        
        return *this;
    }
} // namespace Physics::Collisions

#include "RigidBody.h"
#include "GameObject.h"
#include "Scene.h"

#include <algorithm>
#include <limits>
#include "LibMaths.h"
#include "3DCollisions.h"
#include "SegmentHit.h"

namespace Physics
{
    typedef Collisions::SegmentHit  SegmentHit;
    typedef Core::Maths::Segment    Segment;
    typedef std::numeric_limits<float> FloatLimit;

    RigidBody::RigidBody():
        _useGravity     { BASE_USE_GRAVITY },
        _mass           { BASE_MASS },
        _friction       { BASE_FRICTION },
        _velocity       { Vec3::zero }
    {}

    RigidBody::RigidBody(bool useGravity, float mass, float friction):
        _useGravity     { useGravity },
        _mass           { mass },
        _friction       { friction },
        _velocity       { Vec3::zero }
    {}

    RigidBody::RigidBody(const RigidBody& r):
        _useGravity     { r._useGravity },
        _mass           { r._mass },
        _friction       { r._friction },
        _velocity       { r._velocity }
    {}

    RigidBody& RigidBody::operator=(const RigidBody& r) 
    {
        _useGravity = r._useGravity;
        _mass       = r._mass;
        _friction   = r._friction;
        _velocity   = r._velocity;

        return *this;    
    }

    RigidBody&  RigidBody::physicUpdate(Scene& scene, Transform& transform,
                              Collider* collider,  float deltaTime) noexcept
    {
        // Update gravity and friction
        updateGravity(deltaTime);
        updateFriction(deltaTime);

        // If the rigid body is moving
        if (collider && !_velocity.equals(Vec3::zero, std::numeric_limits<float>::epsilon()))
        {
            if (!collider->isTrigger())
                physicCollider(scene, transform, collider, deltaTime);
            else
                physicTrigger(scene, collider, deltaTime);
            // Move the GameObject
            transform.translateUpdate(_velocity * deltaTime);
        }

        return *this;
    }

    RigidBody& RigidBody::physicCollider(Scene& scene, Transform& transform, 
                                       Collider* collider, float deltaTime) noexcept
    {
        SegmentHit* lowestHit { nullptr };

        // Get the lowest hit and the result of the normal of each object
        Vec3 norm = physicResultNormal(scene, collider, deltaTime, lowestHit);

        // Set the position to the lowest hit if we hit something
        if (lowestHit)
        {
            transform.setPosition(lowestHit->intersection);
            delete lowestHit;
        }
        // Reduce the veolcity using the normal
        _velocity -= norm;

        return *this;
    }

    Vec3 RigidBody::physicResultNormal(Scene& scene, Collider* collider,
                                       float deltaTime, SegmentHit*& lowestHit) noexcept
    {
        std::list<GameObject*>& gameObjects { scene.objects() };
        SegmentHit* hit { nullptr };
        Vec3 normSum { Vec3::zero };
        // Check the collisions for each gameObject
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        {
            // If the gameObject is active and has a collider try to collide
            if ((*it) && (*it)->isActive() && (*it)->hasCollider() &&
                (*it)->checkCollision(collider, _velocity, deltaTime, hit))
            {
                Collider* otherCollider { (*it)->collider() };
                otherCollider->onCollision(scene, collider, hit);
                // If it is a trigger don't collide
                if (otherCollider->isTrigger())
                    delete hit;
                else
                {
                    checkLowestHit(hit, lowestHit, normSum);
                    collider->onCollision(scene, otherCollider, hit);
                }
                hit = nullptr;
            }
        }

        return normSum;
    }

    RigidBody&  RigidBody::checkLowestHit(  SegmentHit*& hit,
                                            SegmentHit*& lowestHit,
                                            Vec3& normSum) noexcept
    {
        // Update the normal
        normSum += hit->n * _velocity.dot(hit->n);

        // Get the lowest hit
        if (lowestHit)
        {
            if (hit->t < lowestHit->t)
            {
                delete lowestHit;
                lowestHit = hit;
            }
            else
                delete hit;
        }
        else
        {
            lowestHit = hit;
        }

        return *this;
    }

    RigidBody& RigidBody::physicTrigger(Scene& scene, Collider* collider, float deltaTime) noexcept
    {
        std::list<GameObject*>& gameObjects { scene.objects() };
        SegmentHit* hit { nullptr };

        // Check the collisions for each gameObject
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        {
            // If the gameObject is active and has a collider try to collide
            if ((*it) && (*it)->isActive() && (*it)->hasCollider() &&
                !(*it)->collider()->isTrigger() &&
                (*it)->checkCollision(collider, _velocity, deltaTime, hit))
            {
                collider->onCollision(scene, (*it)->collider(), hit);
                delete hit;
                hit = nullptr;
            }
        }

        return *this;
    }

    RigidBody& RigidBody::updateGravity(float deltaTime) noexcept
    {
        // If the rigidBody uses the gravity
        if (_useGravity)
        {
            // Update the y velocity using the gravity
            _velocity.y -= _mass * s_gravity * deltaTime;
        } 

        return *this;
    }

    RigidBody& RigidBody::updateFriction(float deltaTime) noexcept
    {
        _velocity -= _velocity * (_friction * deltaTime);
        if (_velocity.squaredLength() < 0.01f)
            _velocity = Vec3::zero;

        return *this;
    }

    bool RigidBody::isGrounded(Scene& scene,
                               const Transform& transform,
                               Collider* collider) noexcept
    {
        if (!collider)
            return false;

        Vec3 b = transform.position();
        b.y -= collider->getHalfHeight();
        Segment ab {transform.position(), b};
        SegmentHit* hit { nullptr };

        std::list<GameObject*>& gameObjects { scene.objects() };
        // Check the collisions for each gameObject
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        {
            // If the gameObject is active and has a collider try to collide
            if ((*it) && (*it)->isActive() && (*it)->hasCollider() && !(*it)->collider()->isTrigger() &&
                (*it)->collideWithSegment(ab, hit))
            {
                delete hit;
                return true;
            }
        }

        return false;
    }

    RigidBody&  RigidBody::addForce(const Vec3& force) noexcept
    {
        _velocity += force;

        return *this;
    }
}
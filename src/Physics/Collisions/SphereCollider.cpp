#include "SphereCollider.h"
#include "Sphere.h"
#include "OBox.h"
#include "3DCollisions.h"
#include "Hit.h"
#include "Transform.h"

namespace Physics::Collisions
{
    #pragma region Constructors
    SphereCollider::SphereCollider(GameObject* gO, bool isTrigger):
        Collider(gO, isTrigger)
    {}

    SphereCollider::SphereCollider(const SphereCollider& collider) :
        Collider (collider),
        _sph { collider._sph }
    {}
    #pragma endregion

    #pragma region Operators
    SphereCollider& SphereCollider::operator=(const SphereCollider& collider)
    {
        Collider::operator=(collider);
        _sph = collider._sph;

        return *this;
    }

    Collider* SphereCollider::copy() noexcept 
    {
        return new SphereCollider(*this);
    }
    #pragma endregion

    #pragma region Functions
    Collider& SphereCollider::updateTransform(const Transform& transform) noexcept
    {
        // Change the origin of the box collider
        _sph.origin = transform.position();

        // Create the scale of the box
        _sph.radius = transform.scale().x / 2.0f;

        return *this;
    }

    bool SphereCollider::collideWithSphere(const Sphere& collidingSph, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) const noexcept
    {
        return movingSphereStaticSphere(collidingSph, _sph, speed, deltaTime, hit);
    }

    bool SphereCollider::collideWithOBox(const OBox& collidingBox, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) const noexcept
    {
        (void)collidingBox;
        (void)speed;
        (void)deltaTime;
        (void)hit;
        //We don't have a moving box - static sphere collision
        return false;
    }

    bool SphereCollider::collide(const Collider& collider, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) const noexcept
    {
        return collider.collideWithSphere(_sph, speed, deltaTime, hit);
    }

    bool SphereCollider::collideWithSegment(const Segment& s, SegmentHit*& hit) const noexcept
    {
        return segmentSphere(s, _sph, hit);
    }

    float SphereCollider::getHalfHeight() const noexcept 
    {
        return _sph.radius;
    }

    std::string SphereCollider::type() const noexcept
    {
        return "Sphere";
    }
    #pragma endregion
}
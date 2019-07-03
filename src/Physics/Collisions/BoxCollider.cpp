#include "BoxCollider.h"
#include "Sphere.h"
#include "OBox.h"
#include "3DCollisions.h"
#include "Hit.h"
#include "Transform.h"

namespace Physics::Collisions
{
    #pragma region Constructors
    BoxCollider::BoxCollider(GameObject* gO, bool isTrigger):
        Collider(gO, isTrigger)
    {}

    BoxCollider::BoxCollider(const BoxCollider& collider):
        Collider(collider),
        _box { collider._box }
    {}
    #pragma endregion

    #pragma region Operators
    BoxCollider& BoxCollider::operator=(const BoxCollider& collider)
    {
        Collider::operator=(collider);
        _box = collider._box;

        return *this;
    }

    Collider* BoxCollider::copy() noexcept 
    {
        return new BoxCollider(*this);
    }
    #pragma endregion

    #pragma region Functions
    Collider& BoxCollider::updateTransform(const Transform& transform) noexcept
    {
        // Change the origin of the box collider
        _box.origin.origin = transform.position();

        // create the referential using the rotation
        Mat rotation = Transform::createEulerRotation(transform.rotation());
        _box.origin.i = rotation * Vec3::right;
        _box.origin.j = rotation * Vec3::up;
        _box.origin.k = rotation * Vec3::forward;

        // Create the scale of the box
        _box.halfW = transform.scale().x / 2.0f;
        _box.halfH = transform.scale().y / 2.0f;
        _box.halfD = transform.scale().z / 2.0f;

        return *this;
    }

    bool BoxCollider::collideWithSphere(const Sphere& collidingSph, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) const noexcept
    {
        return movingSphereStaticBox(_box, collidingSph, speed, deltaTime, hit);
    }

    bool BoxCollider::collideWithOBox(const OBox& collidingBox, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) const noexcept
    {
        (void)collidingBox;
        (void)speed;
        (void)deltaTime;
        (void)hit;
        //We don't have a moving box - static box collision
        return false;
    }

    bool BoxCollider::collide(const Collider& collider, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) const noexcept
    {
        return collider.collideWithOBox(_box, speed, deltaTime, hit);
    }

    bool BoxCollider::collideWithSegment(const Segment& s, SegmentHit*& hit) const noexcept
    {
        return segmentOrientedBox(s, _box, hit);
    }

    float BoxCollider::getHalfHeight() const noexcept
    {
        return _box.halfH;
    }

    std::string BoxCollider::type() const noexcept
    {
        return "Box";
    }

    #pragma endregion
}
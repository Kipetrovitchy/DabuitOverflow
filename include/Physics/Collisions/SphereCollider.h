#ifndef __SPHERE_COLLIDER_H__
#define __SPHERE_COLLIDER_H__

#include "Sphere.h"
#include "OBox.h" 
#include "Collider.h"
#include "Vec3.h"
#include "SegmentHit.h"

namespace Physics
{
    class Transform;
}

namespace Physics::Collisions
{

    #pragma region Typedefs
        typedef Core::Maths::Sphere Sphere;
        typedef Core::Maths::OBox   OBox;
        typedef Core::Maths::Vec3   Vec3;
    #pragma endregion

    class SphereCollider : public Collider
    {
        private:
            #pragma region Attributs
            Sphere  _sph;
            #pragma endregion

        public:
            #pragma region Constructors
            SphereCollider() = default;
            SphereCollider(GameObject* gO, bool isTrigger = false);
            SphereCollider(const SphereCollider& collider);
            ~SphereCollider() = default;
            #pragma endregion

            #pragma region Accessors
            inline Sphere&   sph() {return _sph;};
            inline Sphere    sph() const {return _sph;};
            #pragma endregion

            #pragma region Operators
            SphereCollider& operator=(const SphereCollider& collider);
            Collider* copy() noexcept override;
            #pragma endregion

            #pragma region Functions
            Collider& updateTransform(const Transform& transform) noexcept override;

            bool collideWithSphere(const Sphere& collidingSph, const Vec3& speed, 
                float deltaTime, SegmentHit*& hit) const noexcept;
            bool collideWithOBox(const OBox& collidingBox, const Vec3& speed, 
                float deltaTime, SegmentHit*& hit) const noexcept;
            bool collide(const Collider& collider, const Vec3& speed, 
                float deltaTime, SegmentHit*& hit) const noexcept;
            bool collideWithSegment(const Segment& s, SegmentHit*& hit) const noexcept;

            float getHalfHeight() const noexcept override;
            std::string type() const noexcept override;
            #pragma endregion
    };
}

#endif //__BOX_COLLIDER_H__
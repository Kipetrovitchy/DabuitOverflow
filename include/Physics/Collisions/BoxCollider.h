#ifndef __BOX_COLLIDER_H__
#define __BOX_COLLIDER_H__

#include "Sphere.h"
#include "OBox.h"
#include "Collider.h"

namespace Physics
{
    class Transform;
}

namespace Physics::Collisions
{

    #pragma region Typedefs
        typedef Core::Maths::Sphere Sphere;
        typedef Core::Maths::OBox   OBox;
    #pragma endregion

    class BoxCollider : public Collider
    {
        private:
            #pragma region Attributs
            OBox    _box;
            #pragma endregion

        public:
            #pragma region Constructors
            BoxCollider() = default;
            BoxCollider(GameObject* gO, bool isTrigger = false);
            BoxCollider(const BoxCollider& collider);
            ~BoxCollider() = default;
            #pragma endregion

            #pragma region Accessors
            inline OBox&   box() {return _box;};
            inline OBox    box() const {return _box;};
            #pragma endregion

            #pragma region Operators
            BoxCollider& operator=(const BoxCollider& collider);
            Collider* copy() noexcept override;
            #pragma endregion

            #pragma region Functions
            Collider& updateTransform(const Transform& transform) noexcept;
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
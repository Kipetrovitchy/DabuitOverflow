#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <vector>

#include "Sphere.h"
#include "OBox.h"
#include "SegmentHit.h"
#include "Segment.h"

namespace Physics
{
    class Transform;
}

namespace LowRenderer
{
    class GameObject;
}

namespace Resources
{
    class Scene;
}

namespace Physics::Collisions
{
    #pragma region Typedefs
        typedef Core::Maths::Sphere     Sphere;
        typedef Core::Maths::Segment    Segment;
        typedef Core::Maths::OBox       OBox;
        typedef Physics::Transform      Transform;
        typedef LowRenderer::GameObject GameObject;
        typedef Resources::Scene        Scene;
    #pragma endregion

    class Collider
    {
        private:
            #pragma region Attributes
            GameObject* _gameObject;
            bool        _isTrigger;
            #pragma endregion

        public:
            #pragma region Constructors
            Collider();
            Collider(GameObject* gO, bool isTrigger = false);
            Collider(const Collider& c);
            virtual ~Collider() = default;
            #pragma endregion

            #pragma region Accessors
            inline GameObject*& gameObject()        { return _gameObject; };
            inline GameObject*  gameObject() const  { return _gameObject; };
            inline bool&        isTrigger()         { return _isTrigger; };
            inline bool         isTrigger()  const  { return _isTrigger; };
            #pragma endregion

            #pragma region Operators
            Collider& operator=(const Collider& c);
            #pragma endregion

            #pragma region Functions
            virtual Collider* copy() noexcept = 0;
            virtual Collider& updateTransform(const Transform& transform) noexcept = 0;

            virtual bool collideWithSphere(const Sphere& collidingSph, const Vec3& speedSph, 
                float deltaTime, SegmentHit*& hit) const           noexcept = 0;
            virtual bool collideWithOBox(const OBox& collidingBox, const Vec3& speedSph, 
                float deltaTime, SegmentHit*& hit) const           noexcept = 0;
            virtual bool collide(const Collider& collider, const Vec3& speedSph, 
                float deltaTime, SegmentHit*& hit) const           noexcept = 0;
            virtual bool collideWithSegment(const Segment& s, SegmentHit*& hit) const noexcept = 0;

            virtual float getHalfHeight() const noexcept = 0;

            virtual std::string type() const noexcept = 0;

            Collider& onCollision(Scene& scene, Collider* collider, SegmentHit* hit) noexcept;
            
            #pragma endregion

    };
}

#endif //__COLLIDER_H__
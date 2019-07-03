#ifndef __RIGID_BODY_H__
#define __RIGID_BODY_H__

#include <vector>

#include "LibMaths.h"
#include "Transform.h"
#include "Collider.h"
#include "SegmentHit.h"

#define GRAVITY 9.81f
#define BASE_USE_GRAVITY true
#define BASE_MASS 1.0f
#define BASE_FRICTION 0.7f

namespace LowRenderer 
{
    class GameObject;
}

namespace Resources
{
    class Scene;
}

namespace Physics
{
    typedef Core::Maths::Vec3 Vec3;
    typedef LowRenderer::GameObject GameObject;
    typedef Physics::Collisions::Collider Collider;
    typedef Physics::Collisions::SegmentHit SegmentHit;
    typedef Resources::Scene Scene;

    class RigidBody
    {
        private:
            static constexpr float s_gravity { GRAVITY };

            #pragma region Attributes
            bool            _useGravity;
            float           _mass;
            float           _friction;
            Vec3            _velocity;
            #pragma endregion
    
            #pragma region Functions
            RigidBody& updateGravity(float deltaTime) noexcept;
            RigidBody& updateFriction(float deltaTime) noexcept;
            #pragma endregion

        public:
            #pragma region Constructors
            RigidBody();
            RigidBody(bool useGravity, float mass = BASE_MASS, float friction = BASE_FRICTION);
            RigidBody(const RigidBody& r);
            ~RigidBody() = default;
            #pragma endregion
    
            #pragma region Operators
            RigidBody& operator=(const RigidBody& r);
            #pragma endregion
    
            #pragma region Functions
            RigidBody&  physicUpdate(Scene& scene, Transform& transform, 
                                     Collider* collider, float deltaTime) noexcept;
            RigidBody&  physicCollider(Scene& scene, Transform& transform, 
                                       Collider* collider, float deltaTime) noexcept;
            Vec3        physicResultNormal(Scene& scene, Collider* collider,
                                           float deltaTime, SegmentHit*& lowestHit) noexcept;
            RigidBody&  checkLowestHit(SegmentHit*& hit,
                                       SegmentHit*& lowestHit,
                                       Vec3& normSum) noexcept;        
            RigidBody&  physicTrigger(Scene& scene, Collider* collider, float deltaTime) noexcept;
            bool isGrounded(Scene& scene, const Transform& transform, Collider* collider) noexcept;
            
            RigidBody&  addForce(const Vec3& force) noexcept;
            #pragma endregion

            #pragma region Accessors
            inline Vec3& velocity() { return _velocity; };
    };
}

#endif//__RIGID_BODY_H__
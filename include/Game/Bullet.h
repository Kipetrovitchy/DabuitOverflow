#ifndef __BULLET_H__
#define __BULLET_H__

#include "Entity.h"

namespace Physics::Collisions
{
    class Collider;
    class SegmentHit;
}

namespace Game
{
    #pragma region Typedefs
        typedef Resources::Scene                    Scene;
        typedef LowRenderer::GameObject             GameObject;
        typedef Physics::Collisions::Collider       Collider;
        typedef Physics::Collisions::SegmentHit     SegmentHit;
    #pragma endregion

    class Bullet : public GameObject
    {
        private:
            #pragma region Attributes
                Entity*     _owner;
                float       _damage;
            #pragma endregion

        public:
            #pragma region Constructors
                Bullet();
                Bullet(Model* m, Shader* s, const Transform& tr, Entity* owner,
                       float damage);
                Bullet(const Bullet& copy);
                ~Bullet() = default;
            #pragma endregion

            #pragma region Accessors
                Entity*         owner()           { return _owner; }
                float           damage()    const { return _damage; }
                float&          damage()          { return _damage; }
            #pragma endregion

            #pragma region Operators
                Bullet&     operator=(const Bullet& copy);
            #pragma endregion

            #pragma region Functions
                GameObject& update(Scene& scene, float deltaTime) noexcept override;
                GameObject& onTrigger(Scene& scene, Collider* collider,
                                      SegmentHit* hit) noexcept override;
                GameObject& save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept override;
            #pragma endregion
    };
} // namespace Game

#endif //__BULLET_H__